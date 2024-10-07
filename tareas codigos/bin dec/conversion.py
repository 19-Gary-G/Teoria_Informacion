def decimal_a_binario(decimal):
    if decimal == 0:
        return "0"
    binario = ""
    while decimal > 0:
        residuo = decimal % 2
        binario = str(residuo) + binario
        decimal = decimal // 2
    return binario

def binario_a_decimal(binario):
    decimal = 0
    potencia = 0
    for digito in binario[::-1]:
        decimal += int(digito) * (2 ** potencia)
        potencia += 1
    return decimal

def main():
    print("Elige una opcion:")
    print("1. Convertir de decimal a binario")
    print("2. Convertir de binario a decimal")
    
    opcion = input("Opcion: ")

    if opcion == "1":
        numero_decimal = int(input("Introduce un numero en decimal: "))
        resultado = decimal_a_binario(numero_decimal)
        print(f"El numero en binario es: {resultado}")

    elif opcion == "2":
        numero_binario = input("Introduce un numero en binario: ")
        resultado = binario_a_decimal(numero_binario)
        print(f"El numero en decimal es: {resultado}")

    else:
        print("Opción no valida")

if __name__ == "__main__":
    main()
