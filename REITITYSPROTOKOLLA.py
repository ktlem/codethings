"""TIE-02101 Ohjelmointi 1: Johdanto
Tehtävä 12.3 - Reititysprotokollasimulaattori
Kristian Lempinen 296236

Tämä on ohjelma, joka mahdollistaa reitittimien reititystaulujen tietojen tutkimisen, kun reitittimet
kommunikoivat keskenään. Ohjelmaan voi ladata tietoja suoraan ennaltamäärätystä tiedostosta tai syöttää tietoja
käsin. Käyttäjä voi luoda uusia reitittimiä sekä verkkoja, linkittää näitä keskenään ja tulostuskomennoilla saada
tietoonsa reitittimien sen hetkiset yhteydet verkkoihin, sekä muihin reitittimiin."""


# Router on luokka, jolla reitittimiä ja niiden tietoja käsitellään ohjelmassa.

class Router:

    def __init__(self, name):

        self.__name = name
        self.__neighbours = []
        self.__networks = {}

    def __str

    # Metodi, jolla kunkin reitittimen tiedot saadaan tulostettua käyttäjälle.
    def print_info(self):

        print_networks = []

        # Verkot (= Networks) sanakirjasta luodaan lista tulostusta varten.
        for network in self.__networks:
            print_networks.append(network + ":" + str(self.__networks[network]))

        print(" ", self.__name)
        print("    N:", ", ".join(sorted(self.__neighbours)))
        print("    R:", ", ".join(sorted(print_networks)))

    # Ns. naapuri-reitittimien (= Neighbours) lisääminen reitittimen tietoihin.
    def add_neighbour(self, router):
        if router not in self.__neighbours:
            self.__neighbours.append(router.__name)

    # Naapuri-reitittimien palautusta pääohjelmaan tarvitaan reititystaulujen lähettämisessä. (Komento "S").
    def get_neighbours(self):
        return self.__neighbours

    # Verkkojen nimen sekä etäisyyden reitittimestä lisääminen reititin-oliolle.
    def add_network(self, network_name, distance_from_network):
        if network_name not in self.__networks:
            self.__networks[network_name] = distance_from_network

    # Reititystaulun vastaanotto, joka myös antaa reitittimen etäisyyden verkosta.
    def receive_routing_table(self, router):
        for network_name, distance in router.__networks.items():
            self.add_network(network_name, distance + 1)

    # Tällä metodilla tarkistetaan reitittimen etäisyys verkosta.
    def has_route(self, network):
        if network in self.__networks:
            if self.__networks[network] == 0:
                print("Router is an edge router for the network.")
            else:
                print("Network", network, "is", self.__networks[network], "hops away")
        else:
            print("Route to the network is unknown.")


# Funktio, joka lukee käyttäjän antaman syötetiedoston ja muuttaa siinä olevat tiedot oikeaan muotoon ohjelman
# toiminnan kannalta.
def read_from_file(filename):

# Reitittimien nimet ja reititin oliot sisältävä sanakirja, jonka avulla voidaan noutaa pääohjelmassa reititin-olioita
# pääohjelmassa eri komennoille. Jos syötetiedostoa ei ole, tämä luodaan erikseen pääohjelman puolella.
    router_database = {}

    try:
        file = open(filename, "r")
        for line in file:
            data = line.strip().split("!")
            router_database[data[0]] = Router(data[0])

            if len(data) > 0:

                if data[1] != "":
                    neighbours = data[1].split(";")
                    for neighbour in neighbours:
                        router_database[data[0]].add_neighbour(Router(neighbour))

                if data[2] != "":
                    # Mahdollistetaan kaikkien verkkojen luku tiedostosta, jos reitittimellä on niitä useampi.
                    for network in data[2].split(";"):
                        network_name, distance = network.split(":")
                        router_database[data[0]].add_network(network_name, int(distance))

        return router_database

    except (OSError, ValueError, IOError):
        print("Error: the file could not be read or there is something wrong with it.")


def main():

    # Tiedostonluku
    while True:
        router_file = input("Network file: ")
        if router_file != "":
            router_database = read_from_file(router_file)
            if not router_database:
                return
        else:
            router_database = {}

        # Komentotulkki
        while True:
            command = input("> ")
            command = command.upper()

            # Komento, jolla tulostetaan yksittäisen reitittimen tiedot käyttäjälle.
            if command == "P":
                desired_router = input("Enter router name: ")
                if desired_router in router_database:
                    router_database[desired_router].print_info()
                else:
                    print("Router was not found.")

            # Komento, jolla toistetaan tulostuskomento kaikille olemassa oleville reitittimille.
            elif command == "PA":
                for router in router_database:
                    router_database[router].print_info()

            # Komento, jolla lähetetään reitittimen tiedot kyseisen reitittimen naapureille.
            elif command == "S":
                sending_router = input("Sending router: ")
                if sending_router in router_database:
                    for neighbour in router_database[sending_router].get_neighbours():
                        router_database[neighbour].receive_routing_table(router_database[sending_router])

            # Komento, jolla yhdistetään kaksi reititintä toistensa naapureiksi.
            elif command == "C":
                router_one = input("Enter 1st router: ")
                if router_one in router_database:
                    router_two = input("Enter 2nd router: ")

                    if router_two in router_database:
                        router_database[router_one].add_neighbour(router_database[router_two])
                        router_database[router_two].add_neighbour(router_database[router_one])

                    else:
                        print("Router was not found")
                else:
                    print("Router was not found")

            # Komento, jolla olemassa oleva reititin yhdistetään olemassa olevaan verkkoon.
            elif command == "RR":
                desired_router = input("Enter router name: ")

                if desired_router in router_database:
                    desired_network = input("Enter network name: ")
                    router_database[desired_router].has_route(desired_network)

                else:
                    print("Router was not found")

            # Komento, jolla luodaan uusi reititin.
            elif command == "NR":
                name = input("Enter a new name: ")

                if name not in router_database:
                    router_database[name] = Router(name)

                else:
                    print("Name is taken.")

            # Komento, jolla luodaan uusi verkko.
            elif command == "NN":
                router_to_network = input("Enter router name: ")
                if router_to_network in router_database:
                    network = input("Enter network: ")
                    distance = input("Enter distance: ")
                    router_database[router_to_network].add_network(network, distance)
                else:
                    print("Router was not found")

            # Ohjelman päättäminen.
            elif command == "Q":
                print("Simulator closes.")
                return

            # Ohje valideista komennoista, kun käyttäjä syöttää virheellisen komennon.
            else:
                print("Erroneous command!")
                print("Enter one of these commands:")
                print("NR (new router)")
                print("P (print)")
                print("C (connect)")
                print("NN (new network)")
                print("PA (print all)")
                print("S (send routing tables)")
                print("RR (route request)")
                print("Q (quit)")


main()
