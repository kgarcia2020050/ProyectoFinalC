#include <iostream>
#include <fstream>
#include <string>
#include <locale>

using namespace std;

struct Empleado
{
    int id;
    string nombres;
    string apellidos;
    string fechaNacimiento;
    string DPI;
    string direccion;
    string telefono;
    string status = "activo";
};

int obtenerUltimoId()
{
    int ultimoId = 0;
    ifstream file("empleados.txt");
    if (file)
    {
        Empleado emp;
        while (file >> emp.id >> emp.nombres >> emp.apellidos >> emp.fechaNacimiento >> emp.DPI >> emp.direccion >> emp.telefono)
        {
            ultimoId = emp.id;
        }
        file.close();
    }
    return ultimoId;
}

void guardarEmpleado(const Empleado &emp)
{
    ofstream file("empleados.txt", ios::app);
    if (file)
    {
        file << emp.id << " " << emp.nombres << " " << emp.apellidos << " " << emp.fechaNacimiento << " " << emp.DPI << " " << emp.direccion << " " << emp.telefono << " " << emp.status << endl;
        file.close();
    }
    cout << "Empleado agregado con éxito." << endl;
}

void mostrarEmpleados()
{
    ifstream file("empleados.txt");
    if (file)
    {
        Empleado emp;
        while (file >> emp.id >> emp.nombres >> emp.apellidos >> emp.fechaNacimiento >> emp.DPI >> emp.direccion >> emp.telefono >> emp.status)
        {
            if (emp.status == "activo") {
                cout << "ID: " << emp.id << "\nNombres: " << emp.nombres << "\nApellidos: " << emp.apellidos << "\nFecha de Nacimiento: " << emp.fechaNacimiento << "\nDPI: " << emp.DPI << "\nDirección: " << emp.direccion << "\nTeléfono: " << emp.telefono << "\n" << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "No hay empleados registrados." << endl;
    }
}

bool contiene(const string &cadena, const string &termino)
{
    string cadenaLower = cadena;
    string terminoLower = termino;

    for (char &c : cadenaLower)
    {
        c = tolower(c);
    }
    for (char &c : terminoLower)
    {
        c = tolower(c);
    }

    return cadenaLower.find(terminoLower) != string::npos;
}

void buscarEmpleados()
{
    ifstream file("empleados.txt");
    string termino;

    cout << "Ingrese el término de búsqueda (Apellidos, ID empleado,etc.) ";
    cin >> termino;

    if (file)
    {
        Empleado emp;
        bool encontrado = false;

        while (file >> emp.id >> emp.nombres >> emp.apellidos >> emp.fechaNacimiento >> emp.DPI >> emp.direccion >> emp.telefono >> emp.status)
        {
            if (emp.status == "activo") {
                if (contiene(to_string(emp.id), termino) ||
                    contiene(emp.nombres, termino) ||
                    contiene(emp.apellidos, termino) ||
                    contiene(emp.fechaNacimiento, termino) ||
                    contiene(emp.DPI, termino) ||
                    contiene(emp.direccion, termino) ||
                    contiene(emp.telefono, termino))
                {

                    cout << "ID: " << emp.id << "\nNombres: " << emp.nombres << "\nApellidos: " << emp.apellidos << "\nFecha de Nacimiento: " << emp.fechaNacimiento << "\nDPI: " << emp.DPI << "\nDirección: " << emp.direccion << "\nTeléfono: " << emp.telefono << "\n" << endl;
                    encontrado = true;
                }   
            }
        }

        if (!encontrado)
        {
            cout << "No se encontró ningún empleado con el término: " << termino << endl;
        }

        file.close();
    }
    else
    {
        cout << "No hay empleados registrados." << endl;
    }
}

void deleteEmpleado() {
    ifstream file("empleados.txt");
    ofstream temp("temp.txt");
    int idEliminar;
    bool encontrado = false;

    cout << "Ingrese el ID del empleado a eliminar: ";
    cin >> idEliminar;

    if (file && temp) {
        Empleado emp;
        while (file >> emp.id >> emp.nombres >> emp.apellidos >> emp.fechaNacimiento >> emp.DPI >> emp.direccion >> emp.telefono >> emp.status) {
            if (emp.id == idEliminar && emp.status == "activo") {
                emp.status = "eliminado";
                encontrado = true;
                cout << "Empleado con ID " << idEliminar << " ha sido eliminado." << endl;
            }
            temp << emp.id << " " << emp.nombres << " " << emp.apellidos << " " << emp.fechaNacimiento << " " << emp.DPI << " " << emp.direccion << " " << emp.telefono << " " << emp.status << endl;
        }
        if (!encontrado) {
            cout << "No se encontró ningún empleado con el ID: " << idEliminar << endl;
        }

        file.close();
        temp.close();

        // Reemplaza el archivo original con el temporal
        remove("empleados.txt");
        rename("temp.txt", "empleados.txt");
    }
    else {
        cout << "Error al acceder al archivo de empleados." << endl;
    }
}


void main()
{
    setlocale(LC_ALL, "spanish");
    int option;
    int ultimoId = obtenerUltimoId();

    do
    {
        cout << "Menú Principal" << endl;
        cout << "1. Ingreso de datos de empleados" << endl;
        cout << "2. Mostrar lista de empleados" << endl;
        cout << "3. Buscar un empleado" << endl;
        cout << "4. Eliminar registro de empleado" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese la opción: ";
        cin >> option;

        switch (option)
        {
        case 1:
        {
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
            buscarEmpleados();
            break;

        case 4:
            deleteEmpleado();
            break;

        case 5:
            cout << "Saliendo del programa." << endl;
            break;

        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (option != 5);
}
