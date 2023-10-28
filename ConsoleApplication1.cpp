#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <iomanip>
#include <vector>
#include <sstream>

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

int maxIdWidth = 4;
int maxNombreWidth = 8;
int maxApellidoWidth = 9;
int maxFechaWidth = 17;
int maxDPIWidth = 3;
int maxDireccionWidth = 9;
int maxTelefonoWidth = 8;

void calcularAnchoCampos()
{
    ifstream file("empleados.txt");
    if (file)
    {
        Empleado emp;
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string token;

            getline(ss, token, ','); 
            emp.id = stoi(token);

            getline(ss, emp.nombres, ',');
            getline(ss, emp.apellidos, ',');
            getline(ss, emp.fechaNacimiento, ',');
            getline(ss, emp.DPI, ',');
            getline(ss, emp.direccion, ',');
            getline(ss, emp.telefono, ',');
            getline(ss, emp.status, ',');

            if (emp.status == "activo")
            {
                maxIdWidth = max(maxIdWidth, (int)to_string(emp.id).size());
                maxNombreWidth = max(maxNombreWidth, (int)emp.nombres.size());
                maxApellidoWidth = max(maxApellidoWidth, (int)emp.apellidos.size());
                maxFechaWidth = max(maxFechaWidth, (int)emp.fechaNacimiento.size());
                maxDPIWidth = max(maxDPIWidth, (int)emp.DPI.size());
                maxDireccionWidth = max(maxDireccionWidth, (int)emp.direccion.size());
                maxTelefonoWidth = max(maxTelefonoWidth, (int)emp.telefono.size());
            }
        }
        file.close();
    }
}

void imprimirLineaHorizontal()
{
    cout << "+";
    cout << setw(maxIdWidth + 2) << setfill('-') << "";
    cout << "+";
    cout << setw(maxNombreWidth + 2) << "";
    cout << "+";
    cout << setw(maxApellidoWidth + 2) << "";
    cout << "+";
    cout << setw(maxFechaWidth + 2) << "";
    cout << "+";
    cout << setw(maxDPIWidth + 2) << "";
    cout << "+";
    cout << setw(maxDireccionWidth + 2) << "";
    cout << "+";
    cout << setw(maxTelefonoWidth + 2) << "";
    cout << "+";
    cout << endl;
    cout << setfill(' ');
}

void mostrarTablaEmpleados(const vector<Empleado> &empleados)
{
    calcularAnchoCampos();

    if (empleados.empty())
    {
        cout << "No hay empleados para mostrar." << endl;
        return;
    }

    imprimirLineaHorizontal();
    cout << "+ " << setw(maxIdWidth) << left << "ID"
         << " + " << setw(maxNombreWidth) << "Nombres"
         << " + " << setw(maxApellidoWidth) << "Apellidos"
         << " + " << setw(maxFechaWidth) << "Fecha Nacimiento"
         << " + " << setw(maxDPIWidth) << "DPI"
         << " + " << setw(maxDireccionWidth) << "Dirección"
         << " + " << setw(maxTelefonoWidth) << "Teléfono"
         << " +" << endl;
    imprimirLineaHorizontal();

    for (const Empleado &emp : empleados)
    {
        cout << "| " << setw(maxIdWidth) << left << emp.id
             << " | " << setw(maxNombreWidth) << emp.nombres
             << " | " << setw(maxApellidoWidth) << emp.apellidos
             << " | " << setw(maxFechaWidth) << emp.fechaNacimiento
             << " | " << setw(maxDPIWidth) << emp.DPI
             << " | " << setw(maxDireccionWidth) << emp.direccion
             << " | " << setw(maxTelefonoWidth) << emp.telefono
             << " |" << endl;
    }
    imprimirLineaHorizontal();
}

void imprimirEmpleado(const Empleado &emp)
{
    imprimirLineaHorizontal();
    cout << "| " << setw(maxIdWidth) << left << "ID"
         << " | " << setw(maxNombreWidth) << "Nombres"
         << " | " << setw(maxApellidoWidth) << "Apellidos"
         << " | " << setw(maxFechaWidth) << "Fecha Nacimiento"
         << " | " << setw(maxDPIWidth) << "DPI"
         << " | " << setw(maxDireccionWidth) << "Dirección"
         << " | " << setw(maxTelefonoWidth) << "Teléfono"
         << " |" << endl;
    imprimirLineaHorizontal();
    cout << "| " << setw(maxIdWidth) << left << emp.id << " | "
         << setw(maxNombreWidth) << emp.nombres << " | "
         << setw(maxApellidoWidth) << emp.apellidos << " | "
         << setw(maxFechaWidth) << emp.fechaNacimiento << " | "
         << setw(maxDPIWidth) << emp.DPI << " | "
         << setw(maxDireccionWidth) << emp.direccion << " | "
         << setw(maxTelefonoWidth) << emp.telefono << " |" << endl;
    imprimirLineaHorizontal();
}

void lineasDecorativas(int longitud)
{
    cout << "+";
    for (int i = 0; i < longitud; i++)
    {
        cout << "-";
    }
    cout << "+" << endl;
}

int obtenerUltimoId()
{
    int ultimoId = 0;
    ifstream file("empleados.txt");
    string token;
    if (file)
    { 
        Empleado emp;
        while (getline(file, token, ','))
        {
            emp.id = stoi(token); // Convertimos el string a int
            getline(file, emp.nombres, ',');
            getline(file, emp.apellidos, ',');
            getline(file, emp.fechaNacimiento, ',');
            getline(file, emp.DPI, ',');
            getline(file, emp.direccion, ',');
            getline(file, emp.telefono, ',');
            getline(file, emp.status);
            ultimoId = emp.id;
        }
        file.close();
    }
    return ultimoId;
}

void guardarEmpleado(const Empleado &emp)
{
    lineasDecorativas(30);
    ofstream file("empleados.txt", ios::app);
    if (file)
    {
        file << emp.id << "," << emp.nombres << "," << emp.apellidos << "," << emp.fechaNacimiento << "," << emp.DPI << "," << emp.direccion << "," << emp.telefono << "," << emp.status << endl;
        file.close();
        lineasDecorativas(30);
        cout << "Empleado agregado con éxito." << endl;
        lineasDecorativas(30);

        calcularAnchoCampos();

        cout << "\nDatos del empleado guardado:\n";
        imprimirEmpleado(emp);
    }
    else
    {
        cout << "Error al guardar el empleado." << endl;
    }
    lineasDecorativas(30);
}

void mostrarEmpleados()
{
    vector<Empleado> empleadosActivos;

    ifstream file("empleados.txt");
    if (file)
    {
        Empleado emp;
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string token;

            getline(ss, token, ','); 
            emp.id = stoi(token);

            getline(ss, emp.nombres, ',');
            getline(ss, emp.apellidos, ',');
            getline(ss, emp.fechaNacimiento, ',');
            getline(ss, emp.DPI, ',');
            getline(ss, emp.direccion, ',');
            getline(ss, emp.telefono, ',');
            getline(ss, emp.status, ',');

            if (emp.status == "activo")
            {
                empleadosActivos.push_back(emp);
            }
        }
        file.close();
    }

    mostrarTablaEmpleados(empleadosActivos);
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

    lineasDecorativas(30);
    cout << "Ingrese el término de búsqueda (Apellidos, ID empleado,etc.): ";
    cin.ignore();
    getline(cin, termino);
    lineasDecorativas(30);
    vector<Empleado> empleadosEncontrados;

    if (file)
    {
        Empleado emp;
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            string token;

            getline(ss, token, ','); 
            emp.id = stoi(token);
            
            getline(ss, emp.nombres, ',');
            getline(ss, emp.apellidos, ',');
            getline(ss, emp.fechaNacimiento, ',');
            getline(ss, emp.DPI, ',');
            getline(ss, emp.direccion, ',');
            getline(ss, emp.telefono, ',');
            getline(ss, emp.status, ',');
            
            if (emp.status == "activo" && (
                contiene(to_string(emp.id), termino) ||
                contiene(emp.nombres, termino) ||
                contiene(emp.apellidos, termino) ||
                contiene(emp.fechaNacimiento, termino) ||
                contiene(emp.DPI, termino) ||
                contiene(emp.direccion, termino) ||
                contiene(emp.telefono, termino))
            )
            {
                empleadosEncontrados.push_back(emp);
            }
        }

        file.close();
    }

    mostrarTablaEmpleados(empleadosEncontrados);
}

void eliminarEmpleado()
{
    Empleado emp;
    int idEliminar;
    bool encontrado = false;

    fstream file("empleados.txt", ios::in);
    if (!file)
    {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    ofstream temp("temp.txt", ios::out);
    if (!temp)
    {
        cerr << "No se pudo crear el archivo temporal." << endl;
        return;
    }

    lineasDecorativas(30);
    cout << "Ingrese el ID del empleado a eliminar: ";
    cin >> idEliminar;
    cin.ignore();
    lineasDecorativas(30);

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        getline(ss, line, ','); 
        emp.id = stoi(line);
        
        getline(ss, emp.nombres, ',');
        getline(ss, emp.apellidos, ',');
        getline(ss, emp.fechaNacimiento, ',');
        getline(ss, emp.DPI, ',');
        getline(ss, emp.direccion, ',');
        getline(ss, emp.telefono, ',');
        getline(ss, emp.status, ',');

        if (emp.id == idEliminar && emp.status == "activo")
        {
            emp.status = "eliminado";
            encontrado = true;
            char confirmacion;
            lineasDecorativas(30);
            cout << "¿Está seguro de que desea eliminar este registro? (s/n): \n";
            lineasDecorativas(30);
            imprimirEmpleado(emp);
            lineasDecorativas(30);
            cin >> confirmacion;
            if (tolower(confirmacion) == 's')
            {
                lineasDecorativas(30);
                cout << "Empleado con ID " << idEliminar << " ha sido eliminado." << endl;
            }
            else
            {
                emp.status = "activo";
                cout << "Eliminación cancelada." << endl;
            }
        }
        temp << emp.id << "," << emp.nombres << "," << emp.apellidos
             << "," << emp.fechaNacimiento << "," << emp.DPI
             << "," << emp.direccion << "," << emp.telefono
             << "," << emp.status << endl;
    }

    if (!encontrado) {
        cout << "No se encontró un empleado con el ID " << idEliminar << "." << endl;
    }
    lineasDecorativas(30);

    file.close();
    temp.close();
    
    remove("empleados.txt");
    rename("temp.txt", "empleados.txt");
}

void main()
{
    setlocale(LC_ALL, "spanish");
    int option;
    int ultimoId = obtenerUltimoId();

    lineasDecorativas(30);
    cout << "Exitos.com" << endl;
    lineasDecorativas(30);
    cout << "Bienvenido" << endl;

    do
    {
        lineasDecorativas(30);
        cout << "Menú Principal" << endl;
        lineasDecorativas(30);
        cout << "1. Ingreso de datos de empleados" << endl;
        cout << "2. Mostrar lista de empleados" << endl;
        cout << "3. Buscar un empleado" << endl;
        cout << "4. Eliminar registro de empleado" << endl;
        cout << "5. Salir" << endl;
        lineasDecorativas(30);
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
            eliminarEmpleado();
            break;

        case 5:
            lineasDecorativas(30);
            cout << "Saliendo del programa." << endl;
            lineasDecorativas(30);
            break;

        default:
            lineasDecorativas(30);
            cout << "Opción inválida. Intente de nuevo." << endl;
            lineasDecorativas(30);
        }
    } while (option != 5);
}
