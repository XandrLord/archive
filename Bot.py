from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time

options = webdriver.FirefoxOptions()

options.add_argument("--headless")

driver = webdriver.Firefox(executable_path="C:/Users/Alexandr/PycharmProjects/pythonProject1/Firefox/geckodriver.exe", options=options)

X = True
last_time = ""
pre_last_time = ""
zero = ""
point = 0
message_text = ""

try:
    driver.get("https://funpay.ru/lots/575/")

    while X == True:
        try:
            driver.get("https://funpay.ru/lots/575/")
            driver.implicitly_wait(10)

            chat_button = driver.find_element_by_xpath("/html/body/div/div[1]/section/div[2]/div/div[3]/div/div[2]/div/div[3]/div[3]/a").click()
            driver.implicitly_wait(5)

            zero = "1"
        except:
            continue

        try:
            last_time = driver.find_element_by_xpath("/html/body/div/div[1]/section/div[2]/div/div[3]/div/div[2]/div/div[2]/div[2]/div/div[25]/div/div/div[2]/div[1]/div").text
            message_text = driver.find_element_by_xpath("/html/body/div/div[1]/section/div[2]/div/div[3]/div/div[2]/div/div[2]/div[2]/div/div[25]/div/div/div[2]/div[2]").text
        except:
            try:
                last_time = driver.find_element_by_xpath("/html/body/div/div[1]/section/div[2]/div/div[3]/div/div[2]/div/div[2]/div[2]/div/div[24]/div/div/div[2]/div[1]/div").text
                zero = "0"
            except:
                continue

        try:
            point = last_time.find(".")
        except:
            pre_last_time = last_time
            continue

        if last_time != pre_last_time:
            try:
                driver.get("https://discord.com/login")
                driver.implicitly_wait(5)
                try:
                    mail_input = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/div/div/form/div/div/div[1]/div[2]/div[1]/div/div[2]/input")
                    mail_input.clear()
                    mail_input.send_keys("GreatXandrKing@yandex.ru")
                    driver.implicitly_wait(1)

                    password_input = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/div/div/form/div/div/div[1]/div[2]/div[2]/div/input")
                    password_input.clear()
                    password_input.send_keys("Alex14102004")
                    driver.implicitly_wait(1)

                    login_button = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/div/div/form/div/div/div[1]/div[2]/button[2]").click()
                    driver.implicitly_wait(10)

                    all_button = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/div/div/div/div/div[2]/section/div[1]/div[3]/div[2]").click()
                    driver.implicitly_wait(2)

                    open_chat_button = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/div/div/div/div/div[2]/div/div[1]/div/div[1]/div/div/div[2]/div[1]").click()
                    driver.implicitly_wait(4)

                    text_input = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/div/div/div/div/div[2]/div[2]/main/form/div/div[1]/div/div[3]/div[2]")
                    if (zero != "0") and (point == -1):
                        text_input.send_keys(":" + last_time[::-1] + " ta egasseM weN")
                        driver.implicitly_wait(1)
                        text_input.send_keys(Keys.ENTER)
                        driver.implicitly_wait(1)
                        text_input.send_keys("'" + message_text[::-1] + "'")
                        driver.implicitly_wait(1)
                        text_input.send_keys(Keys.ENTER)
                        driver.implicitly_wait(1)
                    elif (zero == "0") and (point == -1):
                        text_input.send_keys(last_time[::-1] + " ta epyT suoremuN fo egasseM weN")
                        driver.implicitly_wait(1)
                        text_input.send_keys(Keys.ENTER)
                        driver.implicitly_wait(1)
                    elif (zero != "0") and (point != -1):
                        text_input.send_keys(":" + last_time[::-1] + " no egasseM tsaL")
                        driver.implicitly_wait(1)
                        text_input.send_keys(Keys.ENTER)
                        driver.implicitly_wait(1)
                        text_input.send_keys("'" + message_text[::-1] + "'")
                        driver.implicitly_wait(1)
                        text_input.send_keys(Keys.ENTER)
                        driver.implicitly_wait(1)
                    driver.implicitly_wait(1)
                except:
                    try:
                        mail_input = driver.find_element_by_xpath("/html/body/div/div[2]/div/div/div/form/div/div/div[1]/div[2]/div[1]/div/div[2]/input")
                        mail_input.clear()
                        mail_input.send_keys("GreatXandrKing@yandex.ru")
                        driver.implicitly_wait(1)

                        password_input = driver.find_element_by_xpath("/html/body/div/div[2]/div/div/div/form/div/div/div[1]/div[2]/div[2]/div/input")
                        password_input.clear()
                        password_input.send_keys("Alex********")
                        driver.implicitly_wait(1)

                        login_button = driver.find_element_by_xpath("/html/body/div/div[2]/div/div/div/form/div/div/div[1]/div[2]/button[2]").click()
                        time.sleep(10)

                        all_button = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/div/div/div/div/div[2]/section/div[1]/div[3]/div[2]").click()
                        driver.implicitly_wait(2)

                        open_chat_button = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/div/div/div/div/div[2]/div/div[1]/div/div[1]/div/div/div[2]/div[1]").click()
                        driver.implicitly_wait(4)

                        text_input = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/div/div/div/div/div[2]/div[2]/main/form/div/div[1]/div/div[3]/div[2]")
                        if (zero != "0") and (point == -1):
                            text_input.send_keys(":" + last_time[::-1] + " ta egasseM weN")
                            driver.implicitly_wait(1)
                            text_input.send_keys(Keys.ENTER)
                            driver.implicitly_wait(1)
                            text_input.send_keys("'" + message_text[::-1] + "'")
                            driver.implicitly_wait(1)
                            text_input.send_keys(Keys.ENTER)
                            driver.implicitly_wait(1)
                        elif (zero == "0") and (point == -1):
                            text_input.send_keys(last_time[::-1] + " ta epyT suoremuN fo egasseM weN")
                            driver.implicitly_wait(1)
                            text_input.send_keys(Keys.ENTER)
                            driver.implicitly_wait(1)
                        elif (zero != "0") and (point != -1):
                            text_input.send_keys(":" + last_time[::-1] + " no egasseM tsaL")
                            driver.implicitly_wait(1)
                            text_input.send_keys(Keys.ENTER)
                            driver.implicitly_wait(1)
                            text_input.send_keys("'" + message_text[::-1] + "'")
                            driver.implicitly_wait(1)
                            text_input.send_keys(Keys.ENTER)
                            driver.implicitly_wait(1)
                        driver.implicitly_wait(1)
                    except:
                        try:
                            driver.implicitly_wait(10)
                            all_button = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/div/div/div/div/div[2]/section/div[1]/div[3]/div[2]").click()
                            driver.implicitly_wait(2)

                            open_chat_button = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/div/div/div/div/div[2]/div/div[1]/div/div[1]/div/div/div[2]/div[1]").click()
                            driver.implicitly_wait(4)

                            text_input = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/div/div/div/div/div[2]/div[2]/main/form/div/div[1]/div/div[3]/div[2]")
                            if (zero != "0") and (point == -1):
                                text_input.send_keys(":" + last_time[::-1] + " ta egasseM weN")
                                driver.implicitly_wait(1)
                                text_input.send_keys(Keys.ENTER)
                                driver.implicitly_wait(1)
                                text_input.send_keys("'" + message_text[::-1] + "'")
                                driver.implicitly_wait(1)
                                text_input.send_keys(Keys.ENTER)
                                driver.implicitly_wait(1)
                            elif (zero == "0") and (point == -1):
                                text_input.send_keys(last_time[::-1] + " ta epyT suoremuN fo egasseM weN")
                                driver.implicitly_wait(1)
                                text_input.send_keys(Keys.ENTER)
                                driver.implicitly_wait(1)
                            elif (zero != "0") and (point != -1):
                                text_input.send_keys(":" + last_time[::-1] + " no egasseM tsaL")
                                driver.implicitly_wait(1)
                                text_input.send_keys(Keys.ENTER)
                                driver.implicitly_wait(1)
                                text_input.send_keys("'" + message_text[::-1] + "'")
                                driver.implicitly_wait(1)
                                text_input.send_keys(Keys.ENTER)
                                driver.implicitly_wait(1)
                            driver.implicitly_wait(1)
                        except:
                            pre_last_time = last_time
                            continue

            except:
                pre_last_time = last_time
                continue

        pre_last_time = last_time
        time.sleep(120)

except Exception as ex:
    print(ex)
finally:
    driver.close()
    driver.quit()
