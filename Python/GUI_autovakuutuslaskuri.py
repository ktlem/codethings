# Tekijä: Kristian Lempinen
# Tässä versiossa ajoneuvot on syötetty tietorakenteina tiedostonluvun sijaan.

"""Autovakuutuslaskuri graafisella käyttöliittymällä. Käyttäjälle tarjotaan valintoja valmiista tietokannasta ja
jokainen valinta vaikuttaa laskurin lopputulokseen."""

from tkinter import *
from tkinter import messagebox
import tkinter.ttk as ttk

# --------------------------------------------------------

"""Tietokanta, joka sisältää Suomen suosituimmat automerkit sekä mallit kaikissa hintaluokissa."""
# Tietokanta EI perustu oikeaan dataan, vaan ohjelman tekijän omaan automarkkinoiden tuntemukseen, parhaan kykynsä
# mukaisesti. Tietokantaa ei ole toteutettu tiedostonluvulla, sillä tiettyjen 'erikoismallien' löytämiseen autojen
# mallimerkinnöistä tarvitaan jonkin asteen tietämystä autoista. Tiettyjä mallinimiä etsivään tiedostonlukijaan olisi
# pitänyt tehdä useampi poikkeus. Oikeaan vakuutusyhtiön vakuutuslaskuriin ei myöskään voi ladata omaa katalogia
# automerkeistä ja malleista.

Audi = ["A1", "A3", "A4", "A5", "A6", "A7", "A8", "Q3", "Q5", "Q7", "RS3 / S3", "RS4 / S4", " RS5 / S5", "RS6 / S6",
        "R8", "TT"]  # R8 = highest risk

BMW = ["1-sarja", "2-sarja", "3-sarja", "4-sarja", "5-sarja", "6-sarja", "7-sarja", "8-sarja", "X1", "X3", "X5",
       "i3", "i8", "M2", "M3", "M4", "M5", "M8", "Z3", "Z4"]  # M8 = highest risk

Chrysler = ["300C", "Neon", "PT Cruiser", "Sebring"]

Citroen = ["2CV", "C1", "C2", "C3", "C4", "C5", "C6", "DS3", "DS5", "Saxo", "Xantia", "Xsara"]

Dodge = ["Avenger", "Caliber", "Challenger", "Charger", "Journey", "Nitro", "RAM", "Viper"]
# Viper = highest risk

Ferrari = ["360 Modena", "430 Scuderia", "458 Italia", "488 GTB", "512 Testarossa", "550M Maranello", "599 GTO",
           "612 Scaglietti", "812 Superfast", "Enzo", "F12 Berlinetta", "F40", "F50", "FF", "LaFerrari"]

Fiat = ["124 Spider", "500 / 500L / 500X", "Barchetta", "Bravo", "Multipla", "Punto", "Stilo", "Uno"]

Ford = ["C-Max", "Escort", "Fiesta", "Focus", "Fusion", "GT", "Ka", "Kuga", "Mondeo", "Mustang", "Ranger", "Sierra",
        "Thunderbird", "Transit"]  # GT, Mustang = highest risk

Honda = ["Accord", "Civic", "CR-V", "CR-X", "HR-V", "Integra", "Jazz", "Legend", "NSX", "Prelude", "S2000"]
# NSX = high risk

Hyundai = ["Accent", "Coupe", "Elantra", "Genesis", "Getz", "i30", "i40", "Santa Fe", "Sonata", "Veloster"]

Jaguar = ["E-Type", "F-Type", "S-Type", "X-Type", "XE", "XF", "XFR-S", "XJ", "XK"]

KIA = ["Cee'd", "Magentis", "Opirus", "Rio", "Sorento", "Soul", "Sportage", "Stinger"]

Lada = ["2101", "110", "Niva", "Samara"]

Lamborghini = ["Aventador", "Countach", "Diablo", "Gallardo", "Huracán", "Murcielago", "Urus"]

Mazda = ["2", "3", "323", "6", "626", "CX-30", "Familia", "MX-5", "RX-7", "RX-8"]

Mercedes = ["A-sarja", "B-sarja", "C-sarja", "CLK", "E-sarja", "G-sarja" "S-sarja", "SLK / SLC", "SL", "AMG A/B/C/D/E/S",
            "AMG GT", "Vito"]  # AMG = highest risk

MINI = ["Clubman", "Cooper", "Countryman", "Paceman"]

Mitsubishi = ["Carisma", "Colt", "Eclipse", "Galant", "Lancer", "Outlander", "Pajero"]

Nissan = ["240SX", "350Z / 370Z", "Almera", "GT-R", "Juke", "Maxima", "Micra", "Note", "Primera", "Qashqai", "Silvia",
          "Skyline", "Sunny", "Tiida", "X-Trail"]  # GT-R = highest risk

Opel = ["Ampera", "Astra", "Calibra", "Corsa", "Insignia", "Kadett", "Manta", "Omega", "Vectra"]

Peugeot = ["107", "207", "208", "307", "308", "406", "407", "508", "607", "RCZ"]

Porsche = ["911", "Boxster", "Cayenne", "Cayman", "Macan", "Panamera"]

Renault = ["Clio", "Laguna", "Megane", "Scenic", "Twingo"]

Saab = ["9-3", "9-5", "900", "9000"]

SEAT = ["Altea", "Cordoba", "Exeo", "Ibiza", "Leon", "Toledo"]

Skoda = ["Fabia", "Octavia", "Superb"]

Toyota = ["Auris", "Aygo", "Camry", "Carina", "Celica", "Hiace", "Hilux", "Land Cruiser", "MR2", "Prius", "RAV4",
          "Supra", "Yaris"]  # Supra = high risk

Volkswagen = ["Bora", "Caddy", "Golf", "Jetta", "Kuplavolkkari", "Passat", "Polo", "Transporter", "Vento"]

Volvo = ["240", "740", "S40 / V50", "S60 / V70", "S80", "S90 / V90", "XC70"]

Muu = ["Muu malli..."]


dict_of_manufacturers = {"Valitse merkki...": "Valitse malli...", "Audi": Audi, "BMW": BMW, "Chrysler": Chrysler, "Citroen": Citroen, "Dodge": Dodge,
                         "Ferrari": Ferrari, "Fiat": Fiat, "Ford": Ford, "Honda": Honda, "Hyundai": Hyundai,
                         "Jaguar": Jaguar, "KIA": KIA, "Lada": Lada, "Lamborghini": Lamborghini,
                         "Mazda": Mazda, "Mercedes": Mercedes, "MINI": MINI, "Mitsubishi": Mitsubishi,
                         "Nissan": Nissan, "Opel": Opel, "Peugeot": Peugeot, "Porsche": Porsche, "Renault": Renault,
                         "Saab": Saab, "SEAT": SEAT, "Skoda": Skoda, "Toyota": Toyota, "Volkswagen": Volkswagen,
                         "Volvo": Volvo, "Muu merkki...": Muu}

# --------------------------------------------------------

# Tässä laskurissa kannustetaan ympäristöystävällisyyteen, joten polttoainetyypistä koituu myös vakuutuksen hintaan
# joko lisä, alennus tai ei muutosta valinnasta riippuen. Polttoainetyypit toimivat sanakirjan avaimina ja niiden
# arvoina toimii euromääräinen muutos vakuutuksen kokonaishintaan.
fuel_options = {"Bensiini": 0, "Diesel": 25, "Biopolttoaine": -25}


# Sanakirja, jossa avaimina on autojen eri teholuokat. Avaimien arvopareina on lukuja, jotka toimivat kertoimina
# vakuutuslaskurissa. Esim. jos val = 1; auton vakuutuksen hintaa ei koroteta prosentuaalisesti tehomäärän vuoksi.
# Jos val = 2, niin auton vakuutuksen hinta on normaalia kaksi kertaa kalliimpi.
power_classes = {"15-60 hv": 1, "60-100 hv": 1.1, "100-200 hv": 1.2, "200-350 hv": 1.5, "350-500 hv": 1.7, "500+ hv": 2}

# --------------------------------------------------------

risk_classes = {"Low risk": Citroen + Fiat + Lada + MINI + Peugeot + Renault + SEAT,
                "Mild risk": Honda[:-3] + Honda[-3:] + Hyundai + KIA + Skoda + Toyota[:-2] + Toyota[-2:] + Volkswagen
                             + Opel + Saab,
                "Average risk": Audi[:-2] + Audi[-2:] + Chrysler + Ford[:5] + Ford[5:9] + Ford[9:] + Mazda +
                                Mercedes[-1:-1] + Mercedes[0:9] + Mitsubishi + Nissan[:3] + Nissan[3:] + Volvo,
                "High risk": BMW[:-3] + BMW[-3:] + Dodge[:-1] + Honda[-3:-3] + Jaguar + Toyota[-2:-2],
                "Highest risk": Audi[-2:-2] + BMW[-3:-3] + Dodge[-1:-1] + Ferrari + Ford[5:5] + Ford[9:9] +
                                Lamborghini + Mercedes[-2:-4] + Nissan[3:3] + Porsche}

risk_class_base_prices = {250: risk_classes["Low risk"], 300: risk_classes["Mild risk"],
                          350: risk_classes["Average risk"], 500: risk_classes["High risk"],
                          750: risk_classes["Highest risk"]}

# --------------------------------------------------------

class AutoVakuutusLaskuri:

    """Graafisen käyttöliittymän pääikkuna."""

    def __init__(self):
        self.__interface = Tk()
        self.__interface.geometry("700x500")
        self.__interface.title("Autovakuutuslaskuri")

        self.__mainlabel = Label(text="Laske vakuutuksen hinta autollesi", font=("Verdana", 15))
        self.__mainlabel.pack()

        # --------------------------------------------------------

        """Auton merkin ja mallin valinta. Luo pohjahinnan vakuutukselle, perustuen ohjelmassa määriteltyihin
        riskiluokkiin dictissä risk_class_base_prices."""

        self.__manufacturer = ttk.Combobox(self.__interface, width=25)
        self.__manufacturer["values"] = list(dict_of_manufacturers.keys())
        self.__manufacturer.set("Valitse merkki...")
        self.__manufacturer.pack()

        # Kutsu, jolla saadaan käyttöliittymän ikkunaan päivitettyä comboboxien sisällöt, merkkivalinnan vaihtuessa.
        self.__manufacturer.bind("<<ComboboxSelected>>", lambda x: self.update_models())

        self.__model = ttk.Combobox(self.__interface, width=25)
        self.__model["values"] = dict_of_manufacturers[self.__manufacturer.get()]
        self.__model.set("Valitse malli...")
        self.__model.pack()

        # --------------------------------------------------------

        """Lisävalinnat auton polttoainetyypille, teholle sekä varashälyttimelle. Kaikki nämä valinnat vaikuttavat
        laskurin tulokseen."""

        self.fueltype = ttk.Combobox(self.__interface, width=25)
        self.fueltype["values"] = list(fuel_options.keys())
        self.fueltype.set("Valitse polttoaine...")
        self.fueltype.pack()

        self.horsepower = ttk.Combobox(self.__interface, width=25)
        self.horsepower["values"] = list(power_classes.keys())
        self.horsepower.set("Valitse teholuokka...")
        self.horsepower.pack()

        check_state = BooleanVar()
        check_state.set(False)
        self.alarm = Checkbutton(self.__interface, text="Onko autossasi varashälytin?", var=check_state)
        self.alarm.pack()

        # --------------------------------------------------------

        """Vakuutusbonuksien syöttö"""

        self.__insurance_bonus = Scale(self.__interface, from_=0, to=70, width=10, orient=HORIZONTAL)
        self.__insurance_bonus.pack()

        self.__bonuslabel = Label(text="Valitse nykyinen bonusprosenttisi.", height=2)
        self.__bonuslabel.pack()

        # --------------------------------------------------------

        """Lopullisen vakuutuksen hinnan ilmoittava label, johonka ilmestyy sisältöä vasta 'Hanki vakuutuslaskelma'
        painikkeen painamisen jälkeen."""

        self.__cost_label = Label(text="", font=("Verdana", 10), wraplength=600)
        self.__cost_label.pack()

        """Käyttöliittymän toimintopainikkeet, joilla joko tehdään laskurille ajo tai päätetään ohjelman käyttö."""

        self.__calculate_button = Button(text="Hanki vakuutuslaskelma", bg="azure2", fg="black",
                                         relief=RAISED, width=25, cursor="hand2", command=self.calculate_insurance)
        self.__calculate_button.pack()

        self.__quitbutton = Button(text="Lopeta", bg="azure3", fg="black", relief=RAISED, width=25, cursor="hand2",
                                   command=self.confirm_exit)
        self.__quitbutton.pack()

        # --------------------------------------------------------

        """ns. 'Boilerplate disclaimer' eli pikkupräntti."""

        self.__disclaimer1 = Label(text="Varmistathan vakuutuksesi hinnan oikeellisuuden vakuutusmyyjiltämme.",
                                  font=("Verdana", 7))
        self.__disclaimer2 = Label(text=" Eri polttoainevaihtoehtojen mallikohtainen saatavuus voi vaihdella.",
                                  font=("Verdana", 7))
        self.__disclaimer2.pack()
        self.__disclaimer1.pack()

        # --------------------------------------------------------

    # Metodi, joka resetoi kaikki valinnat auton merkkivalintaa muutettaessa. Tällä estetään merkki-malli kombinaatioit
    # joita ei ole olemassa. Esim. "BMW Civic". Kaikki kentät resetoidaan, jotta ohjelma olisi käyttäjäystävällisempi
    # kun halutaan laskea vakuutusten hinnat esimerkiksi saman talouden useammalle autolle. Lopputuloksessa käyttäjää
    # ohjeistetaan valitsemaan auton merkki uudestaan, jos hän haluaa laskea vakuutuksen hinnan toiselle autolle.
    def update_models(self):
        self.__model["values"] = dict_of_manufacturers[self.__manufacturer.get()]
        self.__model.set("Valitse malli...")
        self.fueltype.set("Valitse polttoaine...")
        self.horsepower.set("Valitse teholuokka...")
        self.alarm = False
        self.__cost_label.configure(text="")

    # Metodi, joka toteuttaa vakuutuksen hinnan laskemisen. Vakuutuksen lopullinen hinta päivitetään .__cost_label
    # kohtaan.
    def calculate_insurance(self):

        try:
            car_model = self.__model.get()
            fuel_rate = fuel_options[self.fueltype.get()]
            power_rate = power_classes[self.horsepower.get()]
            has_alarm = self.alarm
        except KeyError:
            messagebox.showerror("Ajoneuvovakuutuslaskuri", "Ole hyvä ja tee valinta kaikkiin kenttiin ennen laskelman "
                                                            "pyytämistä.")
            return

        # Varashälyttimen tuoma euromääräinen hinnanalennus.
        if has_alarm:
            alarm_discount = -50
        else:
            alarm_discount = 0

        bonus_rate = self.__insurance_bonus.get()

        # Vakuutuksen hinnan laskeminen tapahtuu tässä. Ensin tarkastellaan löytyykö autolle "vakuutusdataa" eli
        # onko se arvona jollekin risk_class_base_prices avaimista.
        for key, val in risk_class_base_prices.items():
            if car_model in val:
                base_price = key

                insurance_cost = float((base_price + fuel_rate + alarm_discount) * power_rate) * (1 - (bonus_rate/100))
                var = StringVar()
                var.set("Vakuutuksen hinta autollesi on " + (str("{:.2f}").format(insurance_cost) + " €/vuosi. " +
                                    "Voit laskea vakuutuksen hinnan toiselle autolle valitsemalla merkin uudelleen."))
                self.__cost_label.configure(textvariable=var)

        # Jos käyttäjä on valinnut Muu merkki / Muu malli, eli pohjatietoa ei ole.
        else:
            no_data_found = messagebox.Message(text="Emme valitettavasti löytäneet autollesi vakuutustietoja. "
                                                    "Ole hyvä ja ole yhteydessä vakuutusmyyjiimme.")
            if no_data_found:
                return

    # --------------------------------------------------------

    """Metodi, joka varmistaa käyttäjältä haluaako hän sulkea ohjelman."""

    def confirm_exit(self):
        popup_query = messagebox.askyesno("Autovakuutuslaskuri", "Haluatko varmasti sulkea sovelluksen?")
        if popup_query:
            self.quit()
        else:
            return

    """Metodi, joka sulkee ohjelman."""

    def quit(self):
        self.__interface.destroy()

    """Metodi, joka käynnistää GUI:n."""

    def launch(self):
        self.__interface.mainloop()

    # --------------------------------------------------------


def main():

    user_interface = AutoVakuutusLaskuri()
    user_interface.launch()


main()
