# Ohjelma, joka auttaa määrittämään onko akvaarion vesi seeprakalalle sopivaa mittaustuloksien pohjalta.

def main():
    # toiminto, joka kysyy mittaustulosten määrän
    samples = input("Enter the number of the measurements: ")
    samples = int(samples)
    if samples <= 0:
        print("Error: the number must be expressed as a positive integer.")

    # toiminto, joka kysyy ensimmäisen mittaustuloksen arvon
    times_measured = 1
    value = 0
    while times_measured <= samples:
        x = str(times_measured)
        result = input("Enter the measurement result " + x + ": ")
        result = float(result)
        if result < 6.0:
            print("The conditions are not suitable for zebra fishes.")
            return
        elif result > 8.0:
            print("The conditions are not suitable for zebra fishes.")
            return
        times_measured += 1
        value += result

        # toiminto, joka kysyy seuraavan mittaustuloksen arvon ja vertaa sitä edelliseen
        while 1 < times_measured <= samples:
            x = str(times_measured)
            previous = result
            result = input("Enter the measurement result " + x + ": ")
            result = float(result)
            if result < 6.0:
                print("The conditions are not suitable for zebra fishes.")
                return
            elif result > 8.0:
                print("The conditions are not suitable for zebra fishes.")
                return
            times_measured += 1
            value += result
            difference = result - previous

            # tarkastelu onko annettujen tulosten erotus liian suuri
            if difference > 1:
                print("The conditions are not suitable for zebra fishes.")
                return
            elif difference < -1:
                print("The conditions are not suitable for zebra fishes.")
                return

        # Ilmoitus sopivista olosuhteista, sekä pH-keskiarvo
        average = value / samples
        average = float(average)
        print("Conditions are suitable for zebra fishes. The average pH is {:.2f}.".format(average))


main()


# sopiva ph 6.0 - 8.0
