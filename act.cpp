#include <iostream>

using namespace std;

template<class T>
class LSLSE;

template<class T>
class node
{
    private:
        T data;
        node<T>* sig;

    public:
        node() : sig(nullptr) {};
        node(T data) : data(data), sig(nullptr) {}
        T getData() const { return data; }
        node<T>* getSig() const { return sig; }
        friend class LSLSE<T>;
};

template<class T>
class LSLSE
{
    private:
        node<T>* lista;

    public:
        LSLSE() : lista(nullptr) {};
        bool vacia() const;
        node<T>* ultimo() const;
        node<T>* primero() const;
        node<T>* anterior(node<T>* pos) const;
        void insertar(node<T>* pos, T elem);
        bool eliminar(node<T>* pos);
        void imprimir() const;
};

template<class T>
void LSLSE<T>::imprimir() const
{
    node<T>* aux = lista;
    while (aux != nullptr)
    {
        cout << aux -> data;
        aux = aux -> sig;
    }
}

template<class T>
bool LSLSE<T>::eliminar(node<T>* pos)
{
    if (vacia() || pos == nullptr)
    {
        return false;
    }
    if (pos == lista)
    {
        lista = lista -> sig;
    }
    else
    {
        anterior(pos) -> sig = pos -> sig;
    }

    delete pos;
    return true;
}

template<class T>
void LSLSE<T>::insertar(node<T>* pos, T elem)
{
    node<T>* aux = new node<T>;
    aux -> data = elem;
    if (pos == nullptr)
    {
        aux -> sig = lista;
        lista = aux;
    }
    else
    {
        aux -> sig = pos -> sig;
        pos -> sig = aux;
    }
}

template<class T>
node<T>* LSLSE<T>::anterior(node<T>* pos) const
{
    if (vacia() || pos == nullptr)
    {
        return nullptr;
    }
    node<T>* aux = lista;
    while (aux != nullptr && aux -> sig != pos)
    {
        aux = aux -> sig;
    }

    return aux;
}

template<class T>
node<T>* LSLSE<T>::primero() const
{
    if (vacia())
    {
        return nullptr;
    }

    return lista;
}


template<class T>
node<T>* LSLSE<T>::ultimo() const
{
    if (vacia())
    {
        return nullptr;
    }

    node<T>* aux = lista;

    while (aux -> sig != nullptr)
    {
        aux = aux -> sig;
    }

    return aux;
}

template<class T>
bool LSLSE<T>::vacia() const
{
    if (lista == nullptr)
        return true;

    return false;
}

class SocioClub
{
    private:
        int NumeroSocio;
        string NombreSocio;
        string Domicilio;
        int AñoIngreso;

    public:
        SocioClub() : NumeroSocio(0), NombreSocio(""), Domicilio(""), AñoIngreso(0) {}
        SocioClub(int numSocio, const string& nombre, const string& domicilio, int añoIngreso) : NumeroSocio(numSocio), NombreSocio(nombre), Domicilio(domicilio), AñoIngreso(añoIngreso) {}
        int getNumeroSocio() const { return NumeroSocio; }
        string getNombreSocio() const { return NombreSocio; }
        string getDomicilioSocio() const { return Domicilio; }

    bool operator < (const SocioClub& otro) const
    {
        return NumeroSocio < otro.NumeroSocio;
    }

    bool operator == (const SocioClub& otro) const
    {
        return NumeroSocio == otro.NumeroSocio;
    }

    friend class LSLSE<SocioClub>;

    friend ostream& operator<<(ostream& os, const SocioClub& socio)
    {
        os << "Número de Socio: " << socio.NumeroSocio
        << ", Nombre: " << socio.NombreSocio
        << ", Domicilio: " << socio.Domicilio
        << ", Año de Ingreso: " << socio.AñoIngreso
        << endl;
        return os;
    }
};

int main()
{
    LSLSE<SocioClub> listaSocios;

    int opcion;
    do
    {
        cout << "\nMenú:\n"
        << "1. Registrar un nuevo socio\n"
        << "2. Dar de baja un socio del club\n"
        << "3. Generar un reporte con los datos de todos los socios\n"
        << "4. Buscar por nombre y domicilio a un socio del club\n"
        << "5. Calcular e imprimir el total de socios registrados\n"
        << "6. Salir\n" << endl
        << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
            {
                int numSocio, añoIngreso;

                string nombre, domicilio;
                cout << "Ingrese el número de socio: ";
                cin >> numSocio;

                cout << "Ingrese el nombre del socio: ";
                cin.ignore();
                getline(cin, nombre);
                
                cout << "Ingrese el domicilio del socio: ";
                getline(cin, domicilio);
                
                cout << "Ingrese el año de ingreso del socio: ";
                cin >> añoIngreso;

                SocioClub nuevoSocio(numSocio, nombre, domicilio, añoIngreso);
                node<SocioClub>* pos = listaSocios.primero();
                
                while (pos != nullptr && pos -> getData() < nuevoSocio)
                {
                    pos = pos -> getSig();
                }

                listaSocios.insertar(listaSocios.anterior(pos), nuevoSocio);
                cout << endl << "Socio registrado exitosamente." << endl;
                break;
            }

            case 2:
            {
                int numSocio;
                
                cout << "Ingrese el número de socio a dar de baja: ";
                cin >> numSocio;

                SocioClub socioABorrar;
                node<SocioClub>* pos = listaSocios.primero();
                
                while (pos != nullptr && pos -> getData().getNumeroSocio() != numSocio)
                {
                    pos = pos -> getSig();
                }

                if (pos != nullptr && pos -> getData().getNumeroSocio() == numSocio)
                {
                    socioABorrar = pos -> getData();
                    listaSocios.eliminar(pos);

                    cout << endl << "Socio dado de baja exitosamente." << endl;
                }
                else
                {
                    cout << endl << "No se encontró ningún socio con ese número." << endl;
                }
                break;
            }

            case 3:
            {
                cout << endl << "Reporte de socios:" << endl;
                listaSocios.imprimir();
                cout << endl;
                break;
            }

            case 4:
            {
                string nombre, domicilio;
                
                cout << "Ingrese el nombre del socio a buscar: ";
                cin.ignore();
                getline(cin, nombre);
                
                cout << "Ingrese el domicilio del socio a buscar: ";
                getline(cin, domicilio);

                bool encontrado = false;
                
                node<SocioClub>* pos = listaSocios.primero();
                
                while (pos != nullptr)
                {
                    if (pos -> getData().getNombreSocio() == nombre && pos -> getData().getDomicilioSocio() == domicilio)
                    {
                        cout << endl << "Socio encontrado:" << endl << pos -> getData() << endl;
                        encontrado = true;
                        break;
                    }
                    pos = pos -> getSig();
                }
                
                if (!encontrado)
                {
                    cout << endl << "Socio no encontrado." << endl;
                }
                break;
            }

            case 5:
            {
                int totalSocios = 0;

                node<SocioClub>* pos = listaSocios.primero();

                while (pos != nullptr)
                {
                    totalSocios++;
                    pos = pos -> getSig();
                }

                cout << endl << "Total de socios registrados: " << totalSocios << endl;
                break;
            }

            case 6:
            {
                cout << endl << "Saliendo del programa." << endl;
                break;
            }

            default:
            {
                cout << endl << "Opción inválida, por favor seleccione nuevamente." << endl;
                break;
            }
        }
    } while (opcion != 6);

    return 0;
}
