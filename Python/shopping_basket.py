"""
Author: Kristian Lempinen

OHJELMA: KAUPPAKORI
Ohjelma auttaa käyttäjää löytämään missä hänen kannattaisi käydä ostoksilla, kun katsotaan ostoskorin hintaa.
Ohjelma sisältää kolme toimintoa;
1) Ohjelma voi tulostaa kaikkien vertailussa mukana olevien kauppojen tuotevalikoimat hintoineen.
2) Ohjelma voi tulostaa kaikkien vertailussa mukana olevien tuotteiden listauksen ja näiden alimman hinnan.
3) Ohjelma voi etsiä käyttäjälle mistä hän saisi hankittua hänen määrittelmänsä ostoskorin sisällön edullisimmin.
   Ohjelma laskee samalla myös käyttäjän ostoskorille hinnan.

"""

DEFAULT_FILENAME = "products.txt"


def read_input_file(DEFAULT_FILENAME):
    stores = {}

    file = open(DEFAULT_FILENAME, "r")
    for row in file:
        row = row.split(":")

        if row[0] not in stores:
            stores[row[0]] = {}

        stores[row[0]][row[1]] = float(row[2])

    data = stores
    return data


def print_selections(data):
    for store in sorted(data):
        print(store)
        for item in sorted(data[store]):
            print(f"    {item:<15s} {data[store][item]:>10.2f} e")


def print_known_products(data):
    all_available_products = {}

    print("Available products:")
    for store in sorted(data):
        for item in sorted(data[store]):

            if item not in all_available_products:
                all_available_products[item] = data[store][item]

            else:
                if data[store][item] < all_available_products[item]:
                    all_available_products[item] = data[store][item]

    for item in sorted(all_available_products):
        print(f"    {item:<15s} {all_available_products[item]:>10.2f} e")


def check_stores_for_basket(data):

    desired_products = input("Input product names separated by a white space:\n")
    shopping_basket = desired_products.split()

    baskets_with_prices = {}
    where_basket_possible = {}

    for store in data:
        for item in shopping_basket:
            if item in data[store].keys():
                if store not in baskets_with_prices:
                    baskets_with_prices[store] = {}

                baskets_with_prices[store][item] = data[store][item]

    for store in baskets_with_prices:
        if len(shopping_basket) == len(baskets_with_prices[store].keys()):
            where_basket_possible[store] = baskets_with_prices[store]

    if len(where_basket_possible.keys()) == 0:
        print("There is no store selling all those products.")
        return False

    else:
        return where_basket_possible


def find_cheapest_stores(where_basket_possible):

    cheapest_basket = float(0)
    list_of_cheapest_stores = []

    for store in where_basket_possible:
        basket_total = float(sum(where_basket_possible[store].values()))

        if cheapest_basket == 0:
            cheapest_basket = basket_total
            list_of_cheapest_stores.append(store)

        elif basket_total < cheapest_basket:
            cheapest_basket = basket_total
            list_of_cheapest_stores.clear()
            list_of_cheapest_stores.append(store)

        elif basket_total == cheapest_basket:
            list_of_cheapest_stores.append(store)

    if len(list_of_cheapest_stores) == 1:
        print("The cheapest price for this shopping basket:", list_of_cheapest_stores[0], "for", cheapest_basket, "e")

    else:
        print("Multiple stores sell this basket for", cheapest_basket, "e:", ", ".join(sorted(list_of_cheapest_stores)))


def main():

    data = read_input_file(DEFAULT_FILENAME)

    print("Welcome to the shopping basket optimization app!")
    print("Available commands:")
    print(" S Print all the [S]tores with their available products")
    print(" P Print all the [P]roducts available in all the stores")
    print(" C Show the [C]heapest seller for a specified shopping basket")
    print(" Q [Q]uit")

    while True:
        print()

        command = input("Input command (S, P, C, Q): ")

        if command == "S":
            print_selections(data)

        elif command == "P":
            print_known_products(data)

        elif command == "C":
            where_basket_possible = check_stores_for_basket(data)
            if where_basket_possible:
                find_cheapest_stores(where_basket_possible)

        elif command == "Q":
            print("Bye!")
            return

        else:
            print("Unknown command!?!")


main()
