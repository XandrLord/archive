import telebot
from selenium import webdriver
from selenium.webdriver.common.by import By
from telebot import types
import time

TOKEN = '5086990515:AAGbhLwYh6QcZjoAXZUe95KQ5C_ZbfkV9AI'
bot = telebot.TeleBot(TOKEN)

options = webdriver.FirefoxOptions()
options.add_argument("-headless")
driver = webdriver.Firefox(executable_path="C:/Users/Alexandr/PycharmProjects/LinkBot/geckodriver.exe", options=options)

status = 0

@bot.message_handler(commands=['start'])
def start(message):

    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)

    item1 = types.KeyboardButton('запуск шарманки')
    item2 = types.KeyboardButton('закругляемся')

    markup.add(item1, item2)

    bot.send_message(message.chat.id, "привет, {0.first_name}\nКоманды:\n1) запуск шарманки\n2) закругляемся".format(message.from_user, bot.get_me()), reply_markup=markup)

@bot.message_handler(content_types=["text"])
def orders(message):

    global status

    k = message.text

    if k == "запуск шарманки":

        if status == 0:

            bot.send_message(message.chat.id, "опять работа...".format(message.from_user, bot.get_me()))

            status = 1

            counter = 0

            while status == 1:

                    try:

                        driver.get("https://epk.guppros.ru/interactive_lists")

                        time.sleep(3)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div/main/div/div/div[2]/div/div[2]/button").click()
                        time.sleep(0.5)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[1]/main/div/div[2]/div/div[1]/div/div/div[1]").click()
                        time.sleep(0.5)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[2]/div/div[2]/div").click()
                        time.sleep(0.5)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[1]/main/div/div[2]/div/div[2]/div/div/div[1]/div[1]/div[2]").click()
                        time.sleep(0.5)

                        driver.find_element(By.ID, "list-item-63-2").click()
                        time.sleep(0.5)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[1]/main/div/div[2]/div/div[3]/div/div/div[1]/div[1]/div[2]").click()
                        time.sleep(0.5)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[4]/div/div[6]/div").click()
                        time.sleep(0.5)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[1]/main/div/div[2]/div/div[4]/div/div/div[1]/div[1]/div[2]").click()
                        time.sleep(0.5)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[5]/div/div[9]/div").click()
                        time.sleep(0.5)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[1]/main/div/div[2]/div/div[5]/div/div/div[1]/div[1]/div[2]").click()
                        time.sleep(0.5)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[6]/div/div[3]/div").click()
                        time.sleep(0.5)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[1]/main/div/div[2]/div/div[6]/div/div/div[1]/div[1]/div[2]").click()
                        time.sleep(0.5)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[7]/div/div[2]/div").click()
                        time.sleep(3)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[1]/main/div/div[3]/div[2]/div/div[3]/div[1]/div/div/div/div[1]/div[2]").click()
                        time.sleep(0.5)

                        driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[8]/div/div[4]/div").click()
                        time.sleep(3)

                        list_count = driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[1]/main/div/div[3]/div[2]/div/div[3]/div[2]").text
                        ss = list_count.split()
                        x = int(ss[-1])

                        for i in range(1, x):

                            snils = driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[1]/main/div/div[3]/div[2]/div/div[2]/table/tbody/tr[" + str(i) + "]/td[3]").text

                            if snils == "snils":

                                res = driver.find_element(By.XPATH, "/html/body/div[3]/div/div/div[1]/main/div/div[3]/div[2]/div/div[2]/table/tbody/tr[" + str(i) + "]/td[1]").text
                                bot.send_message(message.chat.id, ("Твой номер в списке: " + res).format(message.from_user, bot.get_me()))

                                break

                        counter = 0

                        time.sleep(1800)

                    except:

                        counter += 1

                        if counter < 100:

                            continue

                        else:

                            status = 0

                            bot.send_message(message.chat.id, "произошла ошибка, вынужден окончить работу".format(message.from_user, bot.get_me()))

        else:

            bot.send_message(message.chat.id, "работа и так идёт полным ходом".format(message.from_user, bot.get_me()))

    elif k == "закругляемся":

        if status == 1:

            status = 0

            bot.send_message(message.chat.id, "снова тьма...".format(message.from_user, bot.get_me()))

        else:

            bot.send_message(message.chat.id, "сейчас и так не работаю".format(message.from_user, bot.get_me()))

    else:

        bot.send_message(message.chat.id, "нихуя не понял, но очень инетересно".format(message.from_user, bot.get_me()))


bot.polling(none_stop=True)

