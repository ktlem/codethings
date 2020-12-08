# TIE-02101 Ohjelmointi 1: Johdanto
# Kahvigallup-ohjelma
# Kristian Lempinen 296236
# kristian.lempinen@tuni.fi


TOO_MUCH_COFFEE = 4     # Vakio, jolla määritellään kuinka paljon on "liikaa kahvia" tarkastelun kannalta.


def how_many_cups():

    """
    Funktio, jonka avulla ohjelmalle syötetään gallupin vastaukset tarkastelua varten

    :return: lista kokonaisluvuista
    """

    responses = []
    while True:
        cups = input()
        if cups == "":      # Tulosteiden syötön päättäminen, kun kaikki vastaukset on annettu
            break
        else:
            responses.append(int(cups))
    return responses


def non_coffee_drinkers(responses):

    """
    Funktio, joka poistaa datasta vastaajat, jotka eivät juo kahvia ja palauttaa tämän arvon raportointia varten

    :param responses: lista kokonaisluvuista
    :return: lista kokonaisluvuista josta on poistettu nollat, poistettujen nollien määrä
    """

    removed = responses.count(0)
    while 0 in responses:
        responses.remove(0)
    return responses, removed


def coffee_data(responses):

    """
    Funktio, joka tutkii vastauksia ja luo niistä pylväskaavion, sekä palauttaa tiedon yleisimmästä vastauksesta

    :param responses: lista kokonaisluvuista, josta on poistettu nollat
    :return: useiten esiintyvä kokonaisluku
    """

    if len(responses) > 0:
        print("Information related to coffee drinkers:")
        most_common = 0
        most_common_amount = 0

        for cups in range(min(responses), max(responses) + 1):       # Pylväskaavion visuaalisesti toteuttava printteri
            amounts = responses.count(cups)
            print("{:2d}".format(cups), amounts * "#")               # Yksittäisen pylväskaavion rivin tulostus

            if amounts > most_common_amount:      # Yleisimmän vastauksen määrittely pääohjelmalle palauttamista varten
                most_common = cups
                most_common_amount = amounts
        return most_common


def percentage(responses, too_much_coffee):

    """
    Funktio, joka kertoo käyttäjälle kuinka suuri prosentuaalinen osuus vastaajista juo liikaa kahvia.
    Tämä 'liika-arvo' määritellään pääohjelman alussa parametrinä, joten raja-arvoa voidaan tarvittaessa muuttaa.

    :param responses: lista kokonaisluvuista, josta on poistettu nollat
    :param too_much_coffee: numeerinen vakio
    :return: desimaaliluku
    """

    heavy_drinkers = 0
    total = 0

    for cups in responses:
        total += 1

        if cups > too_much_coffee:
            heavy_drinkers += 1

    percent = float((heavy_drinkers / total) * 100)     # Tarkastelu liikakäyttäjien %-osuudesta kaikista vastanneista
    return percent


def main():

    print("Enter one response per line. End by entering an empty row.")
    # Vastausten syöttö ohjelmalle.
    responses = how_many_cups()

    # Ei-kahvinjuojien poistaminen gallup-tuloksista vastausten tarkastelua varten.
    responses, removed = non_coffee_drinkers(responses)
    if removed > 0:
        print("Removed", removed, "non-coffee-drinkers responses")
        print("")

    # Vältetäään tyhjän vastausjoukon tarkastelu
    if len(responses) > 0:

        # Pylväskaavio vastauksista. Hankkii myös pääohjelmalle tiedon yleisimmästä vastauksesta.
        most_common = coffee_data(responses)
        print("")

        # Kuppimäärällisesti suurimman vastauksen raportointi käyttäjälle.
        greatest = max(responses)
        print("The greatest response:", greatest, "cups of coffee per day")

        # Yleisimmän vastauksen raportointi käyttäjälle.
        print("The most common response:", most_common, "cups of coffee per day")

        # Kahvin liikakäyttäjien raportointi käyttäjälle.
        percent = percentage(responses, TOO_MUCH_COFFEE)
        if percent > 0:
            print("{:.1f}% of the respondents drink more than".format(percent), TOO_MUCH_COFFEE,
                  "cups of coffee per day")

        elif percent == 0:    # Tilanne, jossa liikakäyttäjiä ei ole.
            print("None of the respondents drink too much coffee")


main()
