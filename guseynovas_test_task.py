import nest_asyncio
import asyncio
import logging
import gspread
from oauth2client.service_account import ServiceAccountCredentials
from aiogram import Bot, Dispatcher, types, F
from aiogram.filters.command import Command
from aiogram.utils.keyboard import InlineKeyboardBuilder
from aiogram.types import FSInputFile, Message
from aiogram.utils.media_group import MediaGroupBuilder
from datetime import datetime
from yoomoney import Quickpay

def get_keyboard():
    # Создаем клавиатуру с кнопками
    buttons = [
        [
            types.InlineKeyboardButton(text="Адрес", callback_data="button_address"),
            types.InlineKeyboardButton(text="Оплата", callback_data="button_payment")
        ],
        [
            types.InlineKeyboardButton(text="Картинка", callback_data="button_image"),
            types.InlineKeyboardButton(text="Таблица", callback_data="button_sheet")
        ]
    ]
    keyboard = types.InlineKeyboardMarkup(inline_keyboard=buttons)
    return keyboard

# Применяем патч для поддержки вложенных циклов событий
nest_asyncio.apply()

# Включаем логирование, чтобы не пропустить важные сообщения
logging.basicConfig(level=logging.INFO)

# Объект бота (https://t.me/test_task_gas_bot)
bot = Bot(token="7440865950:AAEk4OAoyLaBUUykTsOxjSwkjEYBEDBpwr4")

# Диспетчер
dp = Dispatcher()

# Словарь для хранения данных пользователя
user_data = {}

# Указываем необходимые области доступа
scope = ["https://spreadsheets.google.com/feeds", "https://www.googleapis.com/auth/drive"]

# Загружаем учетные данные из файла JSON
creds = ServiceAccountCredentials.from_json_keyfile_name("bot1.json", scope)

# Авторизуемся и создаем клиент для работы с Google Таблицами
client = gspread.authorize(creds)

# Открываем таблицу и выбираем лист
# https://docs.google.com/spreadsheets/d/15R5IZ3UcRPCpvcJdhWIKCer9EV787iAWmiTw0oNMlFE/edit?usp=sharing
sheet = client.open("гугл_табличка").sheet1

# Текст приглашения для пользователя
idol_text = "Нажмите на нужную кнопку или введите дату"

# Хэндлер на команду /start
@dp.message(Command("start"))
async def cmd_start(message: types.Message):
    await message.answer("Здравствуйте, нажмите на нужную кнопку", reply_markup=get_keyboard())

@dp.callback_query(F.data.startswith("button_"))
async def callbacks_num(callback: types.CallbackQuery):
    # Получаем значение, связанное с пользователем, или 0, если его нет
    user_value = user_data.get(callback.from_user.id, 0)
    # Разделяем данные callback на части, чтобы получить действие
    action = callback.data.split("_")[1]

    if action == "address":
        # Отправляем сообщение с адресом и ссылкой на карту
        await callback.message.edit_text("Ленина 1:\nhttps://yandex.ru/maps/?text=Ленина1")
        await callback.message.answer(idol_text, reply_markup=get_keyboard())

    elif action == "payment":
        # Создаем объект Quickpay для оплаты
        quickpay = Quickpay(
            receiver="4100118744098768",
            quickpay_form="shop",
            targets="Sponsor this project",
            paymentType="RUB",
            sum=2,
        )
        # Получаем ссылку на оплату
        payment_link_yoomoney = quickpay.base_url
        # Отправляем сообщение с ссылкой на оплату
        await callback.message.edit_text(f'Для оплаты 2 руб. перейдите по ссылке:\n\n[Yoomoney]({payment_link_yoomoney})', parse_mode="Markdown")
        await callback.message.answer(idol_text, reply_markup=get_keyboard())

    elif action == "image":
        # Отправляем сообщение с картинкой
        await callback.message.answer_photo(
            FSInputFile("/content/img1.jpg"),
            caption="Вот картинка"
        )
        await callback.message.delete()
        await callback.message.answer(idol_text, reply_markup=get_keyboard())

    elif action == "sheet":
        try:
            # Получаем значение из ячейки A2 таблицы
            cell_value = sheet.cell(2, 1).value
            await callback.message.edit_text(f"Значение в ячейке A2: {cell_value}")
            await callback.message.answer(idol_text, reply_markup=get_keyboard())

        except gspread.SpreadsheetNotFound:
            # Обрабатываем ошибку, если таблица не найдена
            await callback.message.edit_text("Таблица с именем 'гугл_табличка' не найдена.")
            await callback.message.answer(idol_text, reply_markup=get_keyboard())

        except gspread.GSpreadException as e:
            # Обрабатываем другие ошибки, связанные с Google Таблицами
            await callback.message.edit_text(f"Произошла ошибка при работе с Google Таблицами: {e}")
            await callback.message.answer(idol_text, reply_markup=get_keyboard())

    # Подтверждаем получение callback
    await callback.answer()

@dp.message()
async def handle_date_input(message: types.Message):
    # Получение текста с датой
    date_text = message.text

    try:
        # Проверка корректности даты
        date = datetime.strptime(date_text, "%d.%m.%y")

        # Форматируем дату для сохранения в нужном формате
        formatted_date = date.strftime("%d.%m.%y")

        # Определяем следующую строку для вставки
        next_row = len(sheet.col_values(2)) + 1
        # Обновляем ячейку с новой датой
        sheet.update_cell(next_row, 2, formatted_date)

        await message.answer("дата верна")
        await message.answer(idol_text, reply_markup=get_keyboard())

    except ValueError:
        # Обрабатываем ошибку неверного формата даты
        await message.answer("дата неверна")
        await message.answer(idol_text, reply_markup=get_keyboard())

# Запуск процесса поллинга новых апдейтов
async def main():
    await dp.start_polling(bot)

if __name__ == "__main__":
    asyncio.run(main())