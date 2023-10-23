#include <iostream>
#include <fstream>
#include <string>
#include<locale>

using namespace std;

struct Empleado {
    int id;
    string nombres;
    string apellidos;
    string fechaNacimiento;
    string DPI;
    string direccion;
    string telefono;
};

int obtenerUltimoId() {
    int ultimoId = 0;
    ifstream file("empleados.txt");
    if (file) {
        Empleado emp;
        while (file >> emp.id >> emp.nombres >> emp.apellidos >> emp.fechaNacimiento >> emp.DPI >> emp.direccion >> emp.telefono) {
            ultimoId = emp.id;
        }
        file.close();
    }
    return ultimoId;
}

void guardarEmpleado(const Empleado& emp) {
    ofstream file("empleados.txt", ios::app);
    if (file) {
        file << emp.id << " " << emp.nombres << " " << emp.apellidos << " " << emp.fechaNacimiento << " " << emp.DPI << " " << emp.direccion << " " << emp.telefono << endl;
        file.close();
    }
    cout << "Empleado agregado con éxito." << endl;
}

void mostrarEmpleados() {
    ifstream file("empleados.txt");
    if (file) {
        Empleado emp;
        while (file >> emp.id >> emp.nombres >> emp.apellidos >> emp.fechaNacimiento >> emp.DPI >> emp.direccion >> emp.telefono) {
            cout << "ID: " << emp.id << "\nNombres: " << emp.nombres << "\nApellidos: " << emp.apellidos << "\nFecha de Nacimiento: " << emp.fechaNacimiento << "\nDPI: " << emp.DPI << "\nDirección: " << emp.direccion << "\nTeléfono: " << emp.telefono << "\n" << endl;
        }
        file.close();
    }
    else {
        cout << "No hay empleados registrados." << endl;
    }
}

void main() {
    setlocale(LC_ALL, "spanish");
    int option;
    int ultimoId = obtenerUltimoId();

    do {
        cout << "Menú Principal" << endl;
        cout << "1. Ingreso de datos de empleados" << endl;
        cout << "2. Mostrar lista de empleados" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese la opción: ";
        cin >> option;

        switch (option) {
        case 1: {
            Empleado newEmployee;
            newEmployee.id = ultimoId + 1;
            ultimoId = newEmployee.id;

            cin.ignore();
            cout << "Nombres: ";
            getline(cin, newEmployee.nombres);
            cout << "Apellidos: ";
            getline(cin, newEmployee.apellidos);
            cout << "Fecha de Nacimiento: ";
            getline(cin, newEmployee.fechaNacimiento);
            cout << "DPI: ";
            getline(cin, newEmployee.DPI);
            cout << "Dirección: ";
            getline(cin, newEmployee.direccion);
            cout << "Teléfono: ";
            getline(cin, newEmployee.telefono);

            guardarEmpleado(newEmployee);
            break;
        }

        case 2:
            mostrarEmpleados();
            break;

        case 3:
            cout << "Saliendo del programa." << endl;
            break;

        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (option != 3);

}
