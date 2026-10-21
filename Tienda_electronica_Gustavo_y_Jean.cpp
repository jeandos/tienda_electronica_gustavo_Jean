#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
using namespace std;

// COLORES ANSI
#define RESET "\033[0m"
#define ROJO "\033[31m"
#define VERDE "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL "\033[34m"
#define MORADO "\033[35m"
#define CELESTE "\033[36m"
#define BLANCO "\033[37m"
#define NEGRITA "\033[1m"

// LIMPIAR PANTALLA
void limpiarPantalla() {
    cout << "\033[2J\033[H";
}

// CLASE PRODUCTO
class Producto {
private:
    string nombre;
    string categoria;
    double precio;
    int stock;

public:
    Producto() {
        nombre = "";
        categoria = "";
        precio = 0;
        stock = 0;
    }

    Producto(string n, string c, double p, int s) {
        nombre = n;
        categoria = c;
        precio = p;
        stock = s;
    }

    // GETTERS
    string getNombre() { return nombre; }
    string getCategoria() { return categoria; }
    double getPrecio() { return precio; }
    int getStock() { return stock; }

    // SETTERS
    void setNombre(string n) { nombre = n; }
    void setCategoria(string c) { categoria = c; }

    void setPrecio(double p) {
        if (p >= 0)
            precio = p;
    }

    void setStock(int s) {
        if (s >= 0)
            stock = s;
    }

    // MOSTRAR PRODUCTO
    virtual void mostrar() {
        cout << fixed << setprecision(2);
        cout << CELESTE
             << "\nProducto: " << getNombre()
             << "\nCategoria: " << getCategoria()
             << "\nPrecio: S/ " << getPrecio()
             << "\nStock: " << getStock()
             << RESET << endl;
    }

    virtual ~Producto() {}
};

// CLASE PERSONAL
class Personal {
private:
    string nombre;
    string dni;
    string cargo;
    double sueldo;

public:
    Personal() {
        nombre = "";
        dni = "";
        cargo = "";
        sueldo = 0;
    }

    // Constructor con parámetros añadido
    Personal(string n, string d, string c, double s) {
        nombre = n;
        dni = d;
        cargo = c;
        sueldo = s;
    }

    // GETTERS
    string getNombre() { return nombre; }
    string getDni() { return dni; }
    string getCargo() { return cargo; }
    double getSueldo() { return sueldo; }

    // SETTERS
    void setNombre(string n) { nombre = n; }
    void setDni(string d) { dni = d; }
    void setCargo(string c) { cargo = c; }

    void setSueldo(double s) {
        if (s >= 0)
            sueldo = s;
    }

    // FUNCIONES SEGUN EL CARGO
    void mostrarFunciones() {
        cout << AMARILLO << "\nFunciones del cargo:\n";

        if (cargo == "Vendedor") {
            cout << "- Atender a los clientes.\n";
            cout << "- Recomendar productos.\n";
            cout << "- Realizar ventas.\n";
        }
        else if (cargo == "Cajero") {
            cout << "- Cobrar las compras.\n";
            cout << "- Calcular los pagos.\n";
            cout << "- Entregar comprobantes.\n";
        }
        else if (cargo == "Almacen") {
            cout << "- Controlar el inventario.\n";
            cout << "- Revisar el stock.\n";
            cout << "- Organizar los productos.\n";
        }
        else if (cargo == "Administrador") {
            cout << "- Supervisar la tienda.\n";
            cout << "- Organizar al personal.\n";
            cout << "- Revisar las ventas.\n";
        }
        else if (cargo == "Tecnico") {
            cout << "- Revisar equipos electronicos.\n";
            cout << "- Diagnosticar fallas.\n";
            cout << "- Realizar reparaciones.\n";
        }
        else {
            cout << "- Apoyar en las actividades de la tienda.\n";
        }

        cout << RESET;
    }

    void mostrar() {
        cout << VERDE << fixed << setprecision(2);
        cout << "\nNombre: " << getNombre()
             << "\nDNI: " << getDni()
             << "\nCargo: " << getCargo()
             << "\nSueldo: S/ " << getSueldo()
             << RESET << endl;

        mostrarFunciones();
    }
};

// MENU INTERACTIVO
int menuInteractivo() {
    string opciones[] = {
        "Mostrar productos",
        "Registrar producto",
        "Vender producto",
        "Registrar personal",
        "Mostrar personal y funciones",
        "Salir"
    };

    int seleccion = 0;
    int tecla;

    for (;;) {
        limpiarPantalla();

        cout << MORADO << NEGRITA;
        cout << "======================================================================\n";
        cout << "       TIENDA DE ELECTRONICOS INTERNACIONAL DE GUSTAVO Y JEAN\n";
        cout << "======================================================================\n";
        cout << RESET;

        cout << CELESTE
             << "Usa las flechas para navegar\n";
        cout << "Presiona ENTER para seleccionar\n\n"
             << RESET;

        for (int i = 0; i < 6; i++) {
            if (i == seleccion) {
                cout << VERDE << NEGRITA
                     << " >> " << opciones[i] << " <<\n"
                     << RESET;
            }
            else {
                cout << BLANCO
                     << "    " << opciones[i] << "\n"
                     << RESET;
            }
        }

        tecla = _getch();

        if (tecla == 13)
            return seleccion + 1;

        if (tecla == 0 || tecla == 224) {
            tecla = _getch();

            if (tecla == 72 || tecla == 75) {
                seleccion--;

                if (seleccion < 0)
                    seleccion = 5;
            }
            else if (tecla == 80 || tecla == 77) {
                seleccion++;

                if (seleccion > 5)
                    seleccion = 0;
            }
        }
    }
}

int main() {
    // INVENTARIO INICIAL: 9 PRODUCTOS
    Producto productos[100] = {
        Producto("Laptop_HP", "Computadora", 2500, 5),
        Producto("Laptop_Lenovo", "Computadora", 2800, 4),
        Producto("PC_Gamer", "Computadora", 4500, 3),
        Producto("Samsung_A55", "Celular", 1500, 10),
        Producto("iPhone_15", "Celular", 3200, 6),
        Producto("Tablet_Samsung", "Tablet", 1200, 7),
        Producto("Audifonos_Sony", "Accesorio", 250, 15),
        Producto("Teclado_Logitech", "Accesorio", 180, 12),
        Producto("Mouse_Gamer", "Accesorio", 120, 20)
    };

    int totalProductos = 9;

    // PERSONAL INICIAL: 7 TRABAJADORES
    Personal personal[50] = {
        Personal("Carlos_Perez", "71234567", "Administrador", 3500.00), 
        Personal("Ana_Gomez", "72345678", "Vendedor", 1500.00),
        Personal("Luis_Torres", "73456789", "Vendedor", 1500.00),
        Personal("Maria_Rojas", "74567890", "Cajero", 1400.00),
        Personal("Jorge_Mendoza", "75678901", "Almacen", 1600.00),
        Personal("Pedro_Castillo", "76789012", "Tecnico", 2200.00),
        Personal("Sofia_Ramos", "77890123", "Vendedor", 1500.00)
        
    };
    int totalPersonal = 7;

    int opcion, cantidad, codigo;
    double precio, sueldo;
    string nombre, categoria, dni, cargo;

    for (;;) {
        opcion = menuInteractivo();
        limpiarPantalla();

        switch (opcion) {

        // MOSTRAR PRODUCTOS
        case 1:
            cout << MORADO << NEGRITA
                 << "======= CATALOGO DE PRODUCTOS =======\n"
                 << RESET;

            for (int i = 0; i < totalProductos; i++) {
                cout << AZUL << NEGRITA
                     << "\nCodigo: " << i + 1
                     << RESET;

                productos[i].mostrar();
            }

            cout << "\nTotal de productos: "
                 << totalProductos << endl;
            break;

        // REGISTRAR PRODUCTO
        case 2:
            cout << CELESTE << NEGRITA
                 << "======= REGISTRAR PRODUCTO =======\n"
                 << RESET;

            if (totalProductos >= 100) {
                cout << ROJO
                     << "Inventario lleno.\n"
                     << RESET;
                break;
            }

            cout << "Nombre (sin espacios): ";
            cin >> nombre;

            cout << "Categoria: ";
            cin >> categoria;

            cout << "Precio: S/ ";
            cin >> precio;

            cout << "Stock inicial: ";
            cin >> cantidad;

            if (precio <= 0 || cantidad < 0) {
                cout << ROJO
                     << "Precio o stock invalido.\n"
                     << RESET;
                break;
            }

            productos[totalProductos].setNombre(nombre);
            productos[totalProductos].setCategoria(categoria);
            productos[totalProductos].setPrecio(precio);
            productos[totalProductos].setStock(cantidad);

            totalProductos++;

            cout << VERDE
                 << "Producto registrado correctamente.\n"
                 << RESET;
            break;

        // VENDER PRODUCTO
        case 3:
            cout << CELESTE << NEGRITA
                 << "======= VENDER PRODUCTO =======\n"
                 << RESET;

            cout << "\nProductos disponibles:\n";

            for (int i = 0; i < totalProductos; i++) {
                cout << i + 1 << ". "
                     << productos[i].getNombre()
                     << " | S/ " << fixed << setprecision(2)
                     << productos[i].getPrecio()
                     << " | Stock: "
                     << productos[i].getStock()
                     << endl;
            }

            cout << "\nIngrese codigo del producto: ";
            cin >> codigo;

            if (codigo < 1 || codigo > totalProductos) {
                cout << ROJO
                     << "Codigo incorrecto.\n"
                     << RESET;
                break;
            }

            cout << "Cantidad a vender: ";
            cin >> cantidad;

            if (cantidad <= 0) {
                cout << ROJO
                     << "Cantidad invalida.\n"
                     << RESET;
                break;
            }

            if (productos[codigo - 1].getStock() < cantidad) {
                cout << ROJO
                     << "Stock insuficiente.\n"
                     << RESET;
                break;
            }

            productos[codigo - 1].setStock(
                productos[codigo - 1].getStock() - cantidad
            );

            cout << VERDE << NEGRITA
                 << "\nVENTA REALIZADA\n"
                 << RESET;

            cout << "Producto: "
                 << productos[codigo - 1].getNombre()
                 << "\nCantidad: " << cantidad
                 << "\nPrecio unitario: S/ "
                 << productos[codigo - 1].getPrecio()
                 << "\nTOTAL: S/ "
                 << productos[codigo - 1].getPrecio() * cantidad
                 << endl;
            break;

        // REGISTRAR PERSONAL
        case 4:
            cout << CELESTE << NEGRITA
                 << "======= REGISTRAR PERSONAL =======\n"
                 << RESET;

            if (totalPersonal >= 50) {
                cout << ROJO
                     << "Limite de personal alcanzado.\n"
                     << RESET;
                break;
            }

            cout << "Nombre (sin espacios): ";
            cin >> nombre;

            cout << "DNI (8 digitos): ";
            cin >> dni;

            if (dni.length() != 8) {
                cout << ROJO
                     << "El DNI debe tener 8 digitos.\n"
                     << RESET;
                break;
            }

            {
                bool valido = true;

                for (int i = 0; i < 8; i++) {
                    if (dni[i] < '0' || dni[i] > '9')
                        valido = false;
                }

                if (!valido) {
                    cout << ROJO
                         << "El DNI solo debe contener numeros.\n"
                         << RESET;
                    break;
                }
            }

            cout << "\nCargos disponibles:\n";
            cout << "1. Vendedor\n";
            cout << "2. Cajero\n";
            cout << "3. Almacen\n";
            cout << "4. Administrador\n";
            cout << "5. Tecnico\n";
            cout << "Seleccione cargo: ";
            cin >> codigo;

            switch (codigo) {
                case 1: cargo = "Vendedor"; break;
                case 2: cargo = "Cajero"; break;
                case 3: cargo = "Almacen"; break;
                case 4: cargo = "Administrador"; break;
                case 5: cargo = "Tecnico"; break;
                default:
                    cout << ROJO
                         << "Cargo incorrecto.\n"
                         << RESET;
                    break;
            }

            if (codigo < 1 || codigo > 5)
                break;

            cout << "Sueldo mensual: S/ ";
            cin >> sueldo;

            if (sueldo <= 0) {
                cout << ROJO
                     << "El sueldo debe ser mayor que cero.\n"
                     << RESET;
                break;
            }

            personal[totalPersonal].setNombre(nombre);
            personal[totalPersonal].setDni(dni);
            personal[totalPersonal].setCargo(cargo);
            personal[totalPersonal].setSueldo(sueldo);

            totalPersonal++;

            cout << VERDE
                 << "Personal registrado correctamente.\n"
                 << RESET;
            break;

        // MOSTRAR PERSONAL Y FUNCIONES
        case 5:
            cout << MORADO << NEGRITA
                 << "======= PERSONAL DE LA TIENDA =======\n"
                 << RESET;

            if (totalPersonal == 0) {
                cout << AMARILLO
                     << "No hay personal registrado.\n"
                     << RESET;
            }
            else {
                for (int i = 0; i < totalPersonal; i++) {
                    cout << AZUL << NEGRITA
                         << "\nEMPLEADO " << i + 1
                         << RESET;

                    personal[i].mostrar();
                }

                cout << CELESTE
                     << "\nTotal de trabajadores: "
                     << totalPersonal << endl
                     << RESET;
            }
            break;

        // SALIR
        case 6:
            cout << MORADO << NEGRITA
                 << "Gracias por utilizar la tienda.\n"
                 << RESET;
            return 0;
        }

        cout << "\n" << AMARILLO
             << "Presiona una tecla para continuar..."
             << RESET;

        _getch();
    }

    return 0;
}
