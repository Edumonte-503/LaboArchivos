#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

void registrarVenta()
{
    string producto;
    string entrada;
    double monto;

    cout << "Producto: ";
    if (!getline(cin, producto))
        return;

    if (producto.find_first_not_of(" \t") == string::npos)
    {
        cout << "Escribe el nombre del producto.\n";
        return;
    }

    cout << "Monto en dolares (ejemplo: 2.50): ";
    if (!getline(cin, entrada))
        return;

    istringstream entradaMonto(entrada);
    char sobrante;
    if (!(entradaMonto >> monto) || monto <= 0 || (entradaMonto >> sobrante))
    {
        cout << "Ingresa un monto mayor que cero, usando punto decimal.\n";
        return;
    }

    // ios::app agrega al final del archivo y conserva las ventas anteriores.
    ofstream archivo("ventas.txt", ios::app);
    if (!archivo)
    {
        cout << "No se pudo abrir ventas.txt para guardar la venta.\n";
        return;
    }
archivo << producto << " - $" << fixed << setprecision(2) << monto << '\n';
    archivo.close();

    if (archivo)
        cout << "Venta registrada.\n";
    else
        cout << "No se pudo guardar la venta.\n";
}

void mostrarVentas()
{
    ifstream archivo("ventas.txt");
    if (!archivo)
    {
        cout << "Todavia no hay ventas o no se pudo abrir ventas.txt.\n";
        return;
    }

    cout << "\n--- Ventas registradas ---\n";
    string linea;
    while (getline(archivo, linea))
    {
        cout << linea << '\n';
    }
}

int main()
{
    string opcion;

    do
    {
        cout << "\n--- Registro de ventas ---\n"
             << "1. Registrar venta\n"
             << "2. Mostrar ventas\n"
             << "3. Salir\n"
             << "Elige una opcion: ";

        if (!getline(cin, opcion))
            break;

        if (opcion == "1")
            registrarVenta();
        else if (opcion == "2")
            mostrarVentas();
        else if (opcion == "3")
            cout << "Programa finalizado.\n";
        else
            cout << "Opcion invalida.\n";
    }
    while (opcion != "3");

    return 0;
}