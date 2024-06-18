#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

struct Producto {
    string nombre;
    double precio;
    int cantidadVendida;
    int stock;
    string sintomas;
};

struct Venta {
    string cliente;
    string producto;
    int cantidad;
    double total;
    string fecha;
};

vector<Producto> listaProductos;
vector<Venta> listaVentas;
vector<string> listaClientes;

void menuPrincipal();
void menuVentas();
void menuProductos();
void menuClientes();
void generarReporteProductos();
void agregarProducto();
void actualizarPrecio();
void buscarVentasPorCliente();
void notificarStockBajo(int umbral);
void buscarVentasPorFecha();
void buscarProductosPorSintomas();
bool clienteExiste(const string& cliente);

int main() {
    
    listaProductos.push_back({"Paracetamol", 20.50, 0, 100, "Fiebre, dolor de cabeza"});
    listaProductos.push_back({"Ibuprofeno", 15.75, 0, 50, "Inflamación, dolor"});
    listaProductos.push_back({"Amoxicilina", 30.20, 0, 75, "Infecciones bacterianas"});
    listaProductos.push_back({"Omeprazol", 25.00, 0, 30, "Acidez, reflujo"});
    listaProductos.push_back({"Vitaminas", 40.80, 0, 60, "Deficiencia de vitaminas"});

    menuPrincipal();

    return 0;
}

void menuPrincipal() {
    int opcion;
    do {
        system("cls");
        cout << "==========================================================" << endl;
        cout << "               Bienvenido a Farmacorp                      " << endl;
        cout << "==========================================================" << endl;
        cout << "1. Realizar una venta" << endl;
        cout << "2. Ver inventario de productos" << endl;
        cout << "3. Administrar clientes" << endl;
        cout << "4. Generar reporte de productos más vendidos" << endl;
        cout << "5. Agregar nuevo producto" << endl;
        cout << "6. Actualizar precio de producto" << endl;
        cout << "7. Buscar ventas por cliente" << endl;
        cout << "8. Notificar productos con stock bajo" << endl;
        cout << "9. Buscar ventas por rango de fechas" << endl;
        cout << "10. Buscar productos por sintomas" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                menuVentas();
                break;
            case 2:
                menuProductos();
                break;
            case 3:
                menuClientes();
                break;
            case 4:
                generarReporteProductos();
                break;
            case 5:
                agregarProducto();
                break;
            case 6:
                actualizarPrecio();
                break;
            case 7:
                buscarVentasPorCliente();
                break;
            case 8:
                notificarStockBajo(10);  // Llamar a la función con un umbral de ejemplo
                break;
            case 9:
                buscarVentasPorFecha();  // Llamar a la nueva función
                break;
            case 10:
                buscarProductosPorSintomas();  // Llamar a la nueva función
                break;
            case 0:
                cout << "Gracias por usar Farmacorp." << endl;
                break;
            default:
                cout << "Opción no valida. Intente nuevamente." << endl;
                break;
        }
    } while (opcion != 0);
}

void menuVentas() {
    string cliente, producto;
    int cantidad;
    double total;
    time_t now = time(0);
    char buffer[80];
    tm *ltm = localtime(&now);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", ltm);
    string fecha(buffer);

    cout << "\n----------------------------------------------------------" << endl;
    cout << "                   Realizar una venta                      " << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Ingrese el nombre del cliente: ";
    cin >> cliente;

    if (!clienteExiste(cliente)) {
        listaClientes.push_back(cliente);
    }

    cout << "Productos disponibles:" << endl;
    for (int i = 0; i < listaProductos.size(); ++i) {
        cout << i + 1 << ". " << listaProductos[i].nombre << " (Bs " << fixed << setprecision(2) << listaProductos[i].precio 
             << ") - Stock: " << listaProductos[i].stock << endl;
    }
    cout << "Seleccione el producto (numero): ";
    int opcionProducto;
    cin >> opcionProducto;
    if (opcionProducto < 1 || opcionProducto > listaProductos.size()) {
        cout << "Opción invalida." << endl;
        return;
    }
    producto = listaProductos[opcionProducto - 1].nombre;
    cout << "Ingrese la cantidad: ";
    cin >> cantidad;
    if (cantidad <= 0 || cantidad > listaProductos[opcionProducto - 1].stock) {
        cout << "Cantidad invalida o no hay suficiente stock." << endl;
        return;
    }
    total = cantidad * listaProductos[opcionProducto - 1].precio;
    listaProductos[opcionProducto - 1].cantidadVendida += cantidad;
    listaProductos[opcionProducto - 1].stock -= cantidad;
    listaVentas.push_back({cliente, producto, cantidad, total, fecha});
    cout << "Venta realizada exitosamente." << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Total a pagar: Bs " << fixed << setprecision(2) << total << endl;
    cout << "Fecha de venta: " << fecha << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void menuProductos() {
    cout << "\n----------------------------------------------------------" << endl;
    cout << "             Inventario de productos en Farmacorp          " << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << setw(30) << left << "Nombre" << setw(10) << left << "Precio" << setw(20) << left << "Cantidad Vendida" << setw(10) << left << "Stock" << setw(30) << left << "Síntomas" << endl;
    cout << "----------------------------------------------------------" << endl;
    for (auto &producto : listaProductos) {
        cout << setw(30) << left << producto.nombre << setw(10) << left << "Bs " << fixed << setprecision(2) << producto.precio 
             << setw(20) << left << producto.cantidadVendida << setw(10) << left << producto.stock << setw(30) << left << producto.sintomas << endl;
    }
    cout << "----------------------------------------------------------" << endl;
    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void menuClientes() {
    cout << "\n----------------------------------------------------------" << endl;
    cout << "             Clientes registrados en Farmacorp             " << endl;
    cout << "----------------------------------------------------------" << endl;
    for (int i = 0; i < listaClientes.size(); ++i) {
        cout << i + 1 << ". " << listaClientes[i] << endl;
    }
    cout << "----------------------------------------------------------" << endl;
    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void generarReporteProductos() {
    cout << "\n----------------------------------------------------------" << endl;
    cout << "           Reporte de productos mas vendidos               " << endl;
    cout << "----------------------------------------------------------" << endl;

    // Ordenar productos por cantidad vendida en orden descendente
    sort(listaProductos.begin(), listaProductos.end(), [](const Producto &a, const Producto &b) {
        return a.cantidadVendida > b.cantidadVendida;
    });

    // Mostrar ranking de productos más vendidos
    cout << setw(5) << left << "Rank" << setw(30) << left << "Nombre" << setw(20) << left << "Cantidad Vendida" << endl;
    cout << "----------------------------------------------------------" << endl;
    for (int i = 0; i < listaProductos.size(); ++i) {
        cout << setw(5) << left << i + 1 << setw(30) << left << listaProductos[i].nombre << setw(20) << left << listaProductos[i].cantidadVendida << endl;
    }
    cout << "----------------------------------------------------------" << endl;
    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void agregarProducto() {
    string nombre;
    double precio;
    int stock;
    string sintomas;

    cout << "\n----------------------------------------------------------" << endl;
    cout << "                   Agregar nuevo producto                  " << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Ingrese el nombre del producto: ";
    cin >> nombre;
    cout << "Ingrese el precio del producto: ";
    cin >> precio;
    if (precio < 0) {
        cout << "Precio inválido." << endl;
        return;
    }
    cout << "Ingrese el stock del producto: ";
    cin >> stock;
    if (stock < 0) {
        cout << "Stock invalido." << endl;
        return;
    }
    cout << "Ingrese los sintomas del producto: ";
    cin.ignore();
    getline(cin, sintomas);

    listaProductos.push_back({nombre, precio, 0, stock, sintomas});
    cout << "Producto agregado exitosamente." << endl;
    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void actualizarPrecio() {
    int opcionProducto;
    double nuevoPrecio;

    cout << "\n----------------------------------------------------------" << endl;
    cout << "                   Actualizar precio de producto           " << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Productos disponibles:" << endl;
    for (int i = 0; i < listaProductos.size(); ++i) {
        cout << i + 1 << ". " << listaProductos[i].nombre << " (Bs " << fixed << setprecision(2) << listaProductos[i].precio << ")" << endl;
    }
    cout << "Seleccione el producto (numero): ";
    cin >> opcionProducto;
    if (opcionProducto < 1 || opcionProducto > listaProductos.size()) {
        cout << "Opción invalida." << endl;
        return;
    }

    cout << "Ingrese el nuevo precio: ";
    cin >> nuevoPrecio;
    if (nuevoPrecio < 0) {
        cout << "Precio invalido." << endl;
        return;
    }

    listaProductos[opcionProducto - 1].precio = nuevoPrecio;
    cout << "Precio actualizado exitosamente." << endl;
    cout << "Presione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void buscarVentasPorCliente() {
    string cliente;

    cout << "\n----------------------------------------------------------" << endl;
    cout << "                   Buscar ventas por cliente               " << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Ingrese el nombre del cliente: ";
    cin >> cliente;


}

void notificarStockBajo(int umbral) {

}

void buscarVentasPorFecha() {

}

void buscarProductosPorSintomas() {

}
