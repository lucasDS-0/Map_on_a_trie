template <typename T>
string_map<T>::string_map() : _size(0) , raiz(nullptr), claves({}) {}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
    *this = aCopiar;
} // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    destruir(this->raiz);
    for (int i = 0; i < d.claves.size(); ++i) {
        this->insert(make_pair(d.claves[i],d.at(d.claves[i])));
    }
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    for (int i = 0; i < claves.size(); ++i) {
        delete &this->at(claves[i]);
    }
    claves.clear();
    destruir(raiz);
}

template <class T>
void string_map<T>::insert(const pair<string, T>& value) {
    if (count(value.first) == 1) {
        erase(value.first);
    }
    Nodo* actual = raiz;
    claves.push_back(value.first);
    bool aux = false;
    if (actual == nullptr) {
        actual = new Nodo();
        raiz = actual;
    }
    for (int c = 0; c < value.first.size(); ++c) {
        if (actual->siguientes[char(value.first[c])] == nullptr) {
            actual->siguientes[char(value.first[c])] = new Nodo();
            aux = true;
        }
        actual = actual->siguientes[char(value.first[c])];
    }
    if (aux) {
        this->_size++;
    }
    actual->definicion = new T(value.second);
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    if (count(clave) != 0) {
        return at(clave);
    } else {
        Nodo* actual = raiz;
        claves.push_back(clave);
        bool aux = false;
        if (actual == nullptr) {
            actual = new Nodo();
            raiz = actual;
        }
        for (int c = 0; c < clave.size(); ++c) {
            if (actual->siguientes[char(clave[c])] == nullptr) {
                actual->siguientes[char(clave[c])] = new Nodo();
                aux = true;
            }
            actual = actual->siguientes[char(clave[c])];
        }
        if (aux) {
            this->_size++;
        }
        actual->definicion = new T(0);
        return *actual->definicion;
    }
}

template <typename T>
int string_map<T>::count(const string& clave) const{
    for (int i = 0; i < claves.size(); ++i) {
        if (claves[i] == clave) {
            return 1;
        }
    }
    return 0;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual = this->raiz;
    for (int c = 0; c < clave.size(); ++c) {
        actual = actual->siguientes[char(clave[c])];
    }
    return *actual->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual = this->raiz;
    for (int c = 0; c < clave.size(); ++c) {
        actual = actual->siguientes[char(clave[c])];
    }
    return *actual->definicion;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    this->_size--;
    Nodo* ultimo = this->raiz;
    Nodo* actual = this->raiz;
    claves.erase(claves.begin() + buscarClave(this->claves,clave));
    int d = 0;
    for (int c = 0; c < clave.size(); ++c) {
        int sig = 0;
        for (int i = 0; i < actual->siguientes.size(); ++i) {
            if (actual->siguientes[i] != nullptr) {
                sig++;
            }
        }
        if (sig > 1) {
            ultimo = actual;
            d = c;
        }
        actual = actual->siguientes[char(clave[c])];
    }
    delete &this->at(clave);
    int sig = 0;
    for (int i = 0; i < actual->siguientes.size(); ++i) {
        if (actual->siguientes[i] != nullptr) {
            sig++;
        }
    }
    if (sig == 0) {
        Nodo* aux = ultimo->siguientes[char(clave[d])];
        ultimo->siguientes[char(clave[d])] = nullptr;
        destruir(aux);
    }
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return raiz == nullptr;
}

template <class T>
string_map<T>::Nodo::Nodo() : siguientes(256, nullptr), definicion(nullptr) {}

template <class T>
string_map<T>::Nodo::Nodo(T *def) : siguientes(256, nullptr), definicion(def) {}

template <class T>
string_map<T>::Nodo::~Nodo() {}

template <class T>
void string_map<T>::destruir(Nodo *v) {
    if (v != nullptr) {
        v->definicion = nullptr;
        for (int i = 0; i < v->siguientes.size(); ++i) {
            Nodo* aux = v->siguientes[i];
            v->siguientes[i] = nullptr;
            destruir(aux);
        }
        delete v;
    }
}

template <class T>
int string_map<T>::buscarClave(vector<string> v, const string key) {
    int h = -1;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == key) {
            return i;
        }
    }
    return h;
}