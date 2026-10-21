// PROYECTO DE PROGRAMACION ORIENTADA A OBJETOS
// TIENDA ELECTRONICA INTERNACIONAL DE GUSTAVO Y JEAN

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <ctime>
#include <limits>
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

const int MAX_PRODUCTOS = 100;
const int MAX_PERSONAL = 50;
const int MAX_CLIENTES = 100;
const int STOCK_BAJO = 5;
// FUNCIONES AUXILIARES

void limpiarPantalla() {
    cout << "\033[2J\033[H";
}

// Lee un entero validando que el usuario no escriba letras
int leerEntero(const string& mensaje) {
    int valor;
    cout << mensaje;
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ROJO << "Entrada invalida. " << RESET << mensaje;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}

// Lee un decimal validando la entrada
double leerDouble(const string& mensaje) {
    double valor;
    cout << mensaje;
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ROJO << "Entrada invalida. " << RESET << mensaje;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}

// Lee texto con espacios 
string leerTexto(const string& mensaje) {
    string s;
    do {
        cout << mensaje;
        getline(cin, s);
    } while (s.empty());
    return s;
}

string fechaActual() {
    time_t t = time(0);
    tm* l = localtime(&t);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", l);
    return string(buffer);
}

// JERARQUIA DE PRODUCTOS 
class Producto {
private:
    string nombre;
    string categoria;
    double precio;
    int stock;

public:
    Producto() : nombre(""), categoria(""), precio(0), stock(0) {}

    Producto(string n, string c, double p, int s)
        : nombre(n), categoria(c), precio(p), stock(s) {}

    virtual ~Producto() {}

    // GETTERS
    string getNombre() const { return nombre; }
    string getCategoria() const { return categoria; }
    double getPrecio() const { return precio; }
    int getStock() const { return stock; }

    // SETTERS
    void setNombre(string n) { nombre = n; }
    void setCategoria(string c) { categoria = c; }
    void setPrecio(double p) { if (p >= 0) precio = p; }
    void setStock(int s) { if (s >= 0) stock = s; }

    // Metodo virtual
    virtual void mostrar() const {
        cout << fixed << setprecision(2);
        cout << CELESTE
             << "\nProducto: " << nombre
             << "\nCategoria: " << categoria
             << "\nPrecio: S/ " << precio
             << "\nStock: " << stock
             << RESET << endl;

        if (stock < STOCK_BAJO)
            cout << ROJO << "  (!) STOCK BAJO" << RESET << endl;
    }
};

class Computadora : public Producto {
private:
    int ram;
    string procesador;

public:
    Computadora(string n, double p, int s, int r, string proc)
        : Producto(n, "Computadora", p, s), ram(r), procesador(proc) {}

    void mostrar() const override {
        Producto::mostrar();
        cout << CELESTE
             << "RAM: " << ram << " GB"
             << "\nProcesador: " << procesador
             << RESET << endl;
    }
};

class Celular : public Producto {
private:
    int almacenamiento;
    int camaraMP;

public:
    Celular(string n, double p, int s, int alm, int cam)
        : Producto(n, "Celular", p, s), almacenamiento(alm), camaraMP(cam) {}

    void mostrar() const override {
        Producto::mostrar();
        cout << CELESTE
             << "Almacenamiento: " << almacenamiento << " GB"
             << "\nCamara: " << camaraMP << " MP"
             << RESET << endl;
    }
};

class Tablet : public Producto {
private:
    double pulgadas;
    int almacenamiento;

public:
    Tablet(string n, double p, int s, double pulg, int alm)
        : Producto(n, "Tablet", p, s), pulgadas(pulg), almacenamiento(alm) {}

    void mostrar() const override {
        Producto::mostrar();
        cout << CELESTE
             << "Pantalla: " << pulgadas << " pulgadas"
             << "\nAlmacenamiento: " << almacenamiento << " GB"
             << RESET << endl;
    }
};

class Accesorio : public Producto {
private:
    string compatibilidad;

public:
    Accesorio(string n, double p, int s, string comp)
        : Producto(n, "Accesorio", p, s), compatibilidad(comp) {}

    void mostrar() const override {
        Producto::mostrar();
        cout << CELESTE
             << "Compatibilidad: " << compatibilidad
             << RESET << endl;
    }
};

// CLASE PERSONAL, CLIENTE
class Persona {
private:
    string nombre;
    string dni;

public:
    Persona() : nombre(""), dni("") {}
    Persona(string n, string d) : nombre(n), dni(d) {}
    virtual ~Persona() {}

    string getNombre() const { return nombre; }
    string getDni() const { return dni; }
    void setNombre(string n) { nombre = n; }
    void setDni(string d) { dni = d; }

    // Metodo virtual
    virtual void mostrar() const = 0;
};

class Personal : public Persona {
private:
    string cargo;
    double sueldo;

public:
    Personal() : Persona(), cargo(""), sueldo(0) {}

    Personal(string n, string d, string c, double s)
        : Persona(n, d), cargo(c), sueldo(s) {}

    string getCargo() const { return cargo; }
    double getSueldo() const { return sueldo; }
    void setCargo(string c) { cargo = c; }
    void setSueldo(double s) { if (s >= 0) sueldo = s; }

    void mostrarFunciones() const {
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

    void mostrar() const override {
        cout << VERDE << fixed << setprecision(2);
        cout << "\nNombre: " << getNombre()
             << "\nDNI: " << getDni()
             << "\nCargo: " << cargo
             << "\nSueldo: S/ " << sueldo
             << RESET << endl;

        mostrarFunciones();
    }
};

// CLASE CLIENTE
class Cliente : public Persona {
private:
    string telefono;
    double totalGastado;
    int cantidadCompras;

public:
    Cliente() : Persona(), telefono(""), totalGastado(0), cantidadCompras(0) {}

    Cliente(string n, string d, string tel)
        : Persona(n, d), telefono(tel), totalGastado(0), cantidadCompras(0) {}

    string getTelefono() const { return telefono; }
    double getTotalGastado() const { return totalGastado; }
    int getCantidadCompras() const { return cantidadCompras; }

    // Historial de compras: se actualiza cada vez que compra
    void agregarCompra(double monto) {
        totalGastado += monto;
        cantidadCompras++;
    }

    void mostrar() const override {
        cout << MORADO << fixed << setprecision(2);
        cout << "\nNombre: " << getNombre()
             << "\nDNI: " << getDni()
             << "\nTelefono: " << telefono
             << "\nCompras realizadas: " << cantidadCompras
             << "\nTotal gastado: S/ " << totalGastado
             << RESET << endl;
    }
};
// BOLETA
class ItemBoleta {
private:
    string producto;
    int cantidad;
    double precioUnitario;

public:
    ItemBoleta(string p, int c, double pu)
        : producto(p), cantidad(c), precioUnitario(pu) {}

    string getProducto() const { return producto; }
    int getCantidad() const { return cantidad; }
    double getPrecioUnitario() const { return precioUnitario; }
    double getSubtotal() const { return cantidad * precioUnitario; }
};

class Boleta {
private:
    static int contador;           // miembro estatico: numero correlativo
    static const double IGV;

    int numero;
    string fecha;
    Cliente cliente;               // composicion
    Personal vendedor;             // composicion
    vector<ItemBoleta> items;

public:
    Boleta(const Cliente& c, const Personal& v, const vector<ItemBoleta>& it)
        : cliente(c), vendedor(v), items(it) {
        numero = ++contador;
        fecha = fechaActual();
    }

    int getNumero() const { return numero; }

    double getSubtotal() const {
        double suma = 0;
        for (size_t i = 0; i < items.size(); i++)
            suma += items[i].getSubtotal();
        return suma;
    }

    double getIgv() const { return getSubtotal() * IGV; }
    double getTotal() const { return getSubtotal() + getIgv(); }

    void mostrar() const {
        cout << fixed << setprecision(2);
        cout << AMARILLO << NEGRITA
             << "\n==================================================\n"
             << "                 BOLETA DE VENTA\n"
             << "==================================================\n"
             << RESET << AMARILLO
             << "N°: " << setw(6) << setfill('0') << numero << setfill(' ')
             << "          Fecha: " << fecha
             << "\nCliente:  " << cliente.getNombre()
             << " (DNI " << cliente.getDni() << ")"
             << "\nVendedor: " << vendedor.getNombre()
             << "\n--------------------------------------------------\n";

        for (size_t i = 0; i < items.size(); i++) {
            cout << items[i].getCantidad() << " x "
                 << items[i].getProducto()
                 << "  @ S/ " << items[i].getPrecioUnitario()
                 << "  = S/ " << items[i].getSubtotal() << "\n";
        }

        cout << "--------------------------------------------------\n"
             << "Subtotal:  S/ " << getSubtotal() << "\n"
             << "IGV (18%): S/ " << getIgv() << "\n"
             << NEGRITA
             << "TOTAL:     S/ " << getTotal() << "\n"
             << RESET << endl;
    }
};

int Boleta::contador = 0;
const double Boleta::IGV = 0.18;

// MENU INTERACTIVO
const int NUM_OPCIONES = 9;

int menuInteractivo() {
    string opciones[NUM_OPCIONES] = {
        "Mostrar productos",
        "Registrar producto",
        "Registrar cliente",
        "Mostrar clientes",
        "Registrar personal",
        "Mostrar personal y funciones",
        "Realizar venta (boleta)",
        "Historial de boletas e ingresos",
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
             << "Usa las flechas para navegar\n"
             << "Presiona ENTER para seleccionar\n\n"
             << RESET;

        for (int i = 0; i < NUM_OPCIONES; i++) {
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
                if (seleccion < 0) seleccion = NUM_OPCIONES - 1;
            }
            else if (tecla == 80 || tecla == 77) {
                seleccion++;
                if (seleccion >= NUM_OPCIONES) seleccion = 0;
            }
        }
    }
}

// FUNCIONES QUE USAN POLIMORFISMO (Producto*)
void mostrarProductos(Producto* productos[], int total) {
    cout << MORADO << NEGRITA
         << "======= CATALOGO DE PRODUCTOS =======\n"
         << RESET;

    for (int i = 0; i < total; i++) {
        cout << AZUL << NEGRITA << "\nCodigo: " << i + 1 << RESET;
        productos[i]->mostrar();   // POLIMORFISMO: llama al mostrar() de cada hijo
    }

    cout << "\nTotal de productos: " << total << endl;
}

void registrarProducto(Producto* productos[], int& total) {
    cout << CELESTE << NEGRITA
         << "======= REGISTRAR PRODUCTO =======\n"
         << RESET;

    if (total >= MAX_PRODUCTOS) {
        cout << ROJO << "Inventario lleno.\n" << RESET;
        return;
    }

    cout << "\nTipo de producto:\n"
         << "1. Computadora\n"
         << "2. Celular\n"
         << "3. Tablet\n"
         << "4. Accesorio\n";

    int tipo = leerEntero("Seleccione tipo: ");
    if (tipo < 1 || tipo > 4) {
        cout << ROJO << "Tipo incorrecto.\n" << RESET;
        return;
    }

    string nombre = leerTexto("Nombre: ");
    double precio = leerDouble("Precio: S/ ");
    int stock = leerEntero("Stock inicial: ");

    if (precio <= 0 || stock < 0) {
        cout << ROJO << "Precio o stock invalido.\n" << RESET;
        return;
    }

    switch (tipo) {
    case 1: {
        int ram = leerEntero("RAM (GB): ");
        string proc = leerTexto("Procesador: ");
        productos[total] = new Computadora(nombre, precio, stock, ram, proc);
        break;
    }
    case 2: {
        int alm = leerEntero("Almacenamiento (GB): ");
        int cam = leerEntero("Camara (MP): ");
        productos[total] = new Celular(nombre, precio, stock, alm, cam);
        break;
    }
    case 3: {
        double pulg = leerDouble("Pulgadas de pantalla: ");
        int alm = leerEntero("Almacenamiento (GB): ");
        productos[total] = new Tablet(nombre, precio, stock, pulg, alm);
        break;
    }
    case 4: {
        string comp = leerTexto("Compatibilidad: ");
        productos[total] = new Accesorio(nombre, precio, stock, comp);
        break;
    }
    }

    total++;
    cout << VERDE << "Producto registrado correctamente.\n" << RESET;
}

// CLIENTES
void registrarCliente(Cliente clientes[], int& total) {
    cout << CELESTE << NEGRITA
         << "======= REGISTRAR CLIENTE =======\n"
         << RESET;

    if (total >= MAX_CLIENTES) {
        cout << ROJO << "Limite de clientes alcanzado.\n" << RESET;
        return;
    }

    string nombre = leerTexto("Nombre: ");
    string dni = leerTexto("DNI (8 digitos): ");

    bool valido = (dni.length() == 8);
    for (size_t i = 0; i < dni.length() && valido; i++)
        if (dni[i] < '0' || dni[i] > '9')
            valido = false;

    if (!valido) {
        cout << ROJO << "El DNI debe tener 8 digitos numericos.\n" << RESET;
        return;
    }

    string telefono = leerTexto("Telefono: ");

    clientes[total] = Cliente(nombre, dni, telefono);
    total++;

    cout << VERDE << "Cliente registrado correctamente.\n" << RESET;
}

void mostrarClientes(Cliente clientes[], int total) {
    cout << MORADO << NEGRITA
         << "======= CLIENTES =======\n"
         << RESET;

    if (total == 0) {
        cout << AMARILLO << "No hay clientes registrados.\n" << RESET;
        return;
    }

    for (int i = 0; i < total; i++) {
        cout << AZUL << NEGRITA << "\nCLIENTE " << i + 1 << RESET;
        clientes[i].mostrar();
    }

    cout << CELESTE << "\nTotal de clientes: " << total << RESET << endl;
}

// PERSONAL
void registrarPersonal(Personal personal[], int& total) {
    cout << CELESTE << NEGRITA
         << "======= REGISTRAR PERSONAL =======\n"
         << RESET;

    if (total >= MAX_PERSONAL) {
        cout << ROJO << "Limite de personal alcanzado.\n" << RESET;
        return;
    }

    string nombre = leerTexto("Nombre: ");
    string dni = leerTexto("DNI (8 digitos): ");

    bool valido = (dni.length() == 8);
    for (size_t i = 0; i < dni.length() && valido; i++)
        if (dni[i] < '0' || dni[i] > '9')
            valido = false;

    if (!valido) {
        cout << ROJO << "El DNI debe tener 8 digitos numericos.\n" << RESET;
        return;
    }

    cout << "\nCargos disponibles:\n"
         << "1. Vendedor\n"
         << "2. Cajero\n"
         << "3. Almacen\n"
         << "4. Administrador\n"
         << "5. Tecnico\n";

    int opcionCargo = leerEntero("Seleccione cargo: ");
    string cargo;

    switch (opcionCargo) {
    case 1: cargo = "Vendedor"; break;
    case 2: cargo = "Cajero"; break;
    case 3: cargo = "Almacen"; break;
    case 4: cargo = "Administrador"; break;
    case 5: cargo = "Tecnico"; break;
    default:
        cout << ROJO << "Cargo incorrecto.\n" << RESET;
        return;
    }

    double sueldo = leerDouble("Sueldo mensual: S/ ");
    if (sueldo <= 0) {
        cout << ROJO << "El sueldo debe ser mayor que cero.\n" << RESET;
        return;
    }

    personal[total] = Personal(nombre, dni, cargo, sueldo);
    total++;

    cout << VERDE << "Personal registrado correctamente.\n" << RESET;
}

void mostrarPersonal(Personal personal[], int total) {
    cout << MORADO << NEGRITA
         << "======= PERSONAL DE LA TIENDA =======\n"
         << RESET;

    if (total == 0) {
        cout << AMARILLO << "No hay personal registrado.\n" << RESET;
        return;
    }

    for (int i = 0; i < total; i++) {
        cout << AZUL << NEGRITA << "\nEMPLEADO " << i + 1 << RESET;
        personal[i].mostrar();
    }

    cout << CELESTE << "\nTotal de trabajadores: " << total << RESET << endl;
}

// BOLETA Y VENTAS
void realizarVenta(Producto* productos[], int totalProductos,
                   Cliente clientes[], int totalClientes,
                   Personal personal[], int totalPersonal,
                   vector<Boleta>& boletas) {

    cout << CELESTE << NEGRITA
         << "======= REALIZAR VENTA =======\n"
         << RESET;

    // 1. ELEGIR CLIENTE
    cout << "\nClientes:\n0. Publico general (sin registro)\n";
    for (int i = 0; i < totalClientes; i++)
        cout << i + 1 << ". " << clientes[i].getNombre()
             << " (DNI " << clientes[i].getDni() << ")\n";

    int codCliente = leerEntero("Seleccione cliente: ");
    if (codCliente < 0 || codCliente > totalClientes) {
        cout << ROJO << "Cliente incorrecto.\n" << RESET;
        return;
    }

    Cliente clienteVenta;
    if (codCliente == 0)
        clienteVenta = Cliente("Publico General", "00000000", "-");
    else
        clienteVenta = clientes[codCliente - 1];

    // 2. ELEGIR VENDEDOR
    cout << "\nVendedores:\n";
    bool hayVendedor = false;
    for (int i = 0; i < totalPersonal; i++) {
        if (personal[i].getCargo() == "Vendedor") {
            cout << i + 1 << ". " << personal[i].getNombre() << "\n";
            hayVendedor = true;
        }
    }

    if (!hayVendedor) {
        cout << ROJO << "No hay vendedores registrados.\n" << RESET;
        return;
    }

    int codVendedor = leerEntero("Seleccione vendedor: ");
    if (codVendedor < 1 || codVendedor > totalPersonal ||
        personal[codVendedor - 1].getCargo() != "Vendedor") {
        cout << ROJO << "Vendedor incorrecto.\n" << RESET;
        return;
    }

    // 3. CARRITO DE COMPRAS
    vector<ItemBoleta> carrito;

    for (;;) {
        cout << "\nProductos disponibles:\n" << fixed << setprecision(2);
        for (int i = 0; i < totalProductos; i++) {
            cout << i + 1 << ". " << productos[i]->getNombre()
                 << " | S/ " << productos[i]->getPrecio()
                 << " | Stock: " << productos[i]->getStock() << "\n";
        }

        int cod = leerEntero("\nCodigo del producto (0 = terminar): ");
        if (cod == 0)
            break;

        if (cod < 1 || cod > totalProductos) {
            cout << ROJO << "Codigo incorrecto.\n" << RESET;
            continue;
        }

        int cant = leerEntero("Cantidad: ");
        if (cant <= 0) {
            cout << ROJO << "Cantidad invalida.\n" << RESET;
            continue;
        }

        if (productos[cod - 1]->getStock() < cant) {
            cout << ROJO << "Stock insuficiente.\n" << RESET;
            continue;
        }

        productos[cod - 1]->setStock(productos[cod - 1]->getStock() - cant);
        carrito.push_back(ItemBoleta(productos[cod - 1]->getNombre(),
                                     cant,
                                     productos[cod - 1]->getPrecio()));

        cout << VERDE << "Agregado al carrito.\n" << RESET;
    }

    if (carrito.empty()) {
        cout << AMARILLO << "\nNo se agrego ningun producto. Venta cancelada.\n" << RESET;
        return;
    }

    // 4. GENERAR BOLETA
    Boleta boleta(clienteVenta, personal[codVendedor - 1], carrito);
    boletas.push_back(boleta);

    if (codCliente > 0)
        clientes[codCliente - 1].agregarCompra(boleta.getTotal());

    boleta.mostrar();
}

void mostrarBoletas(const vector<Boleta>& boletas) {
    cout << MORADO << NEGRITA
         << "======= HISTORIAL DE BOLETAS =======\n"
         << RESET;

    if (boletas.empty()) {
        cout << AMARILLO << "No hay ventas registradas.\n" << RESET;
        return;
    }

    double ingresoTotal = 0;
    for (size_t i = 0; i < boletas.size(); i++) {
        boletas[i].mostrar();
        ingresoTotal += boletas[i].getTotal();
    }

    cout << CELESTE << fixed << setprecision(2)
         << "\nTotal de boletas: " << boletas.size()
         << "\nINGRESO TOTAL: S/ " << ingresoTotal
         << RESET << endl;
}

// MAIN
int main() {
    // PRODUCTOS (arreglo de punteros a la clase base -> polimorfismo)
    Producto* productos[MAX_PRODUCTOS];
    int totalProductos = 0;

    productos[totalProductos++] = new Computadora("Laptop_HP", 2500, 5, 16, "Ryzen 5");
    productos[totalProductos++] = new Computadora("Laptop_Lenovo", 2800, 4, 16, "Intel Core i5");
    productos[totalProductos++] = new Computadora("PC_Gamer", 4500, 3, 32, "Ryzen 7");
    productos[totalProductos++] = new Celular("Samsung_A55", 1500, 10, 128, 50);
    productos[totalProductos++] = new Celular("iPhone_15", 3200, 6, 256, 48);
    productos[totalProductos++] = new Tablet("Tablet_Samsung", 1200, 7, 10.5, 128);
    productos[totalProductos++] = new Accesorio("Audifonos_Sony", 250, 15, "Bluetooth / Jack 3.5mm");
    productos[totalProductos++] = new Accesorio("Teclado_Logitech", 180, 12, "PC / Laptop (USB)");
    productos[totalProductos++] = new Accesorio("Mouse_Gamer", 120, 20, "PC / Laptop (USB)");

    // PERSONAL INICIAL
    Personal personal[MAX_PERSONAL] = {
        Personal("Carlos Perez", "71234567", "Administrador", 3500.00),
        Personal("Ana Gomez", "72345678", "Vendedor", 1500.00),
        Personal("Luis Torres", "73456789", "Vendedor", 1500.00),
        Personal("Maria Rojas", "74567890", "Cajero", 1400.00),
        Personal("Jorge Mendoza", "75678901", "Almacen", 1600.00),
        Personal("Pedro Castillo", "76789012", "Tecnico", 2200.00),
        Personal("Sofia Ramos", "77890123", "Vendedor", 1500.00)
    };
    int totalPersonal = 7;

    // CLIENTES INICIALES
    Cliente clientes[MAX_CLIENTES] = {
        Cliente("Juan Quispe", "45678901", "987654321"),
        Cliente("Rosa Mamani", "46789012", "912345678")
    };
    int totalClientes = 2;

    // BOLETAS
    vector<Boleta> boletas;

    for (;;) {
        int opcion = menuInteractivo();
        limpiarPantalla();

        switch (opcion) {
        case 1: mostrarProductos(productos, totalProductos); break;
        case 2: registrarProducto(productos, totalProductos); break;
        case 3: registrarCliente(clientes, totalClientes); break;
        case 4: mostrarClientes(clientes, totalClientes); break;
        case 5: registrarPersonal(personal, totalPersonal); break;
        case 6: mostrarPersonal(personal, totalPersonal); break;
        case 7:
            realizarVenta(productos, totalProductos,
                          clientes, totalClientes,
                          personal, totalPersonal,
                          boletas);
            break;
        case 8: mostrarBoletas(boletas); break;

        case 9:
            // LIBERAR MEMORIA DINAMICA
            for (int i = 0; i < totalProductos; i++)
                delete productos[i];

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
