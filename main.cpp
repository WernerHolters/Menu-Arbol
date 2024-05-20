#include <iostream>

typedef int element;
class Node{
protected:
    element data;
    Node* left;
    Node* right;
public:
    Node(element x);
    Node(Node* leftBrach, element x, Node* rightBranch);

// ACCESO
    element nodeValue() { return data; }
    Node* getLeft() { return left; }    //subarbolIzq
    Node* getRight() { return right; }  //subarbolDrcho
// MODIFICACION
    void newNode(element x) { data = x; }
    void newLeft(Node *l) { left = l; }
    void newRight(Node *r) {right = r; }
};

Node::Node(element x)
{
    data = x;
    right = left = nullptr;
}
Node::Node(Node* leftBranch, element x, Node* rightBranch)
{
    data = x;
    left = leftBranch;
    right = rightBranch;
}
/*-------------------------------------------------------------------------------*/
class Binary_Tree{
protected:
    Node* root;
public:
    Binary_Tree();
    Binary_Tree(Node* r);
    Node* newTree(Node* left, element value, Node* right);
// ACCESO
    Node* getRoot(){ return root; }
// MODIFICACION
    void setRoot(Node* r){ root = r; }
// METODOS PRIVADOS
    void preorden()
    {
        preorden(root);
    }
    void inorden()
    {
        inorden(root);
    }
    void postorden()
    {
        postorden(root);
    }
    void vaciar()
    {
        vaciar(root);
    }
    int numNodos()
    {
        return numNodos(root);
    }
    int altura()
    {
        return altura(root);
    }
    Node* buscar(element buscado)
    {
        return buscar(root, buscado);
    }
    void insertar(element valor)
    {
        root = insertar(root, valor);
    }
    void eliminar(element valor)
    {
        root = eliminar(root, valor);
    }
    void drawTree()
    {
        drawTree(root);
    }
    bool isEmpty()
    {
        if (root == nullptr)
            return true;
        else
            return false;
    }

private:
    // Recosrrido de un árbol binario en preorden
    void preorden(Node *r)
    {
        if (r != nullptr)
        {
            std::cout<< r->nodeValue() << " ";
            preorden (r->getLeft());
            preorden (r->getRight());
        }
    }
    // Recorrido de un árbol binario en inorden
    void inorden(Node *r)
    {
        if (r != nullptr)
        {
            inorden (r->getLeft());
            std::cout << r->nodeValue() << " ";
            inorden (r->getRight());
        }
    }
    // Recorrido de un árbol binario en postorden
    void postorden(Node *r)
    {
        if (r != nullptr)
        {
            postorden (r->getLeft());
            postorden (r->getRight());
            std::cout << r->nodeValue() << " ";
        }
    }
    void vaciar(Node *r)
    {
        if (r != nullptr)
        {
            vaciar(r->getLeft());
            vaciar(r->getRight());
            std::cout << "\nNodo borrado: " << r->nodeValue();
            delete r;
        }
        root = nullptr;
    }
    int numNodos(Node *r)
    {
        if (r == nullptr)
            return 0;
        else
            return 1 + numNodos(r->getLeft()) + numNodos(r->getRight());
    }
    int altura(Node *r)
    {
        if (r == nullptr)
            return 0 ;
        else
        {
            int alturaIz = altura(r->getLeft());
            int alturaDr = altura(r->getRight());
            if (alturaIz > alturaDr)
                return alturaIz + 1;
            else
                return alturaDr + 1;
        }
    }
    Node* buscar(Node* r, element buscado)
    {
        if (r == nullptr)
            std::cout << "Valor no Encontrado: ";
        else if (buscado == r->nodeValue())
            return r;
        else if (buscado < r->nodeValue())
            return buscar(r->getLeft(), buscado);
        else
            return buscar (r->getRight(), buscado);
    }
    Node* insertar(Node* r, element dato)
    {
        if (r == nullptr)
            r = new Node(dato);
        else if (dato < r->nodeValue())
        {
            Node *iz;
            iz = insertar(r->getLeft(), dato);
            r->newLeft(iz);
        }
        else if (dato > r->nodeValue())
        {
            Node *dr;
            dr = insertar(r->getRight(), dato);
            r->newRight(dr);
        }
        else
            std::cout << "Nodo duplicado\n"; // tratamiento de repetición
        return r;
    }

    Node* eliminar(Node *r, element dato)
    {
        if (r == nullptr)
            std::cout << " no se ha encontrador";
        else if (dato < r->nodeValue())
        {
            Node* iz;
            iz = eliminar(r->getLeft(), dato);
            r->newLeft(iz);
        }
        else if (dato > r->nodeValue())
        {
            Node *dr;
            dr = eliminar(r->getRight(), dato);
            r->newRight(dr);
        }
        else // Nodo encontrado
        {
            Node *q;
            q = r; // nodo a quitar del árbol
            if (q->getLeft() == nullptr)
                r = q->getRight(); // figura 16.30
            else if (q->getRight() == nullptr)
                r = q->getLeft(); // figura 16.31
            else
            { // tiene rama izquierda y derecha
                q = reemplazar(q); //figura 16.32
            }
            q = nullptr;
        }
        return r;
    }
    Node* reemplazar(Node* act)
    {
        Node *a, *p;
        p = act;
        a = act->getLeft(); // rama de nodos menores
        while (a->getRight() != NULL)
        {
            p = a;
            a = a->getRight();
        }
        // copia en act el valor del nodo apuntado por a
        act->newNode(a->nodeValue());
        if (p == act) // a es el hijo izquierdo de act
            p->newLeft(a->getLeft()); // enlaza subarbol izquierdo. Fig. 16.32b
        else
            p->newRight(a->getLeft()); // se enlaza subarbol derecho. Fig. 16.32a
        return a;
    }
    void drawTree(Node* raiz, int espacio = 0, int espaciado = 5) {
        if (raiz == nullptr)
            return;

        espacio += espaciado;

        drawTree(raiz->getRight(), espacio);

        std::cout << '\n';
        for (int i = espaciado; i < espacio; i++)
            std::cout << " ";
        std::cout << raiz->nodeValue() << '\n';

        drawTree(raiz->getLeft(), espacio);
    }

};

Binary_Tree::Binary_Tree()
{
    root = nullptr;
}
Binary_Tree::Binary_Tree(Node* r)
{
    root = r;
}

Node* Binary_Tree::newTree(Node* left, element value, Node* right)
{
    return new Node(left, value, right);
}

/*-------------------------------------------------------------------------------*/
void menu(){
    std::cout << "\n------------- M E N U ----------------\n";
    std::cout << "1. Ingresar Valores Pantalla\n";
    std::cout << "2. Mostrar Recorridos\n";
    std::cout << "3. Vaciar Arbol\n";
    std::cout << "4. Eliminar Valor\n";
    std::cout << "5. Verificar si esta Vacio\n";
    std::cout << "6. Dibujar Arbol\n";
    std::cout << "7. Cantidad de Nodos\n";
    std::cout << "8. Altura del Arbol\n";
    std::cout << "9. Verificar si Existe Valor\n";
    std::cout << "10. Usar Valores por Codigo\n";
    std::cout << "11. Obtener Raiz\n";
    std::cout << "Eliga una Opcion: \n";
}
/*-------------------------------------------------------------------------------*/
int main() {
    Node *n1, *n2, *n3, *n4;
    Binary_Tree a1, a2, a3, a4, a;

    int op;
    do
    {
        menu(); std::cin >> op;
        switch (op)
        {
            case 1:
                int numero;
                for (int i = 0; i < 5; ++i) {
                    std::cout << "Ingrese Valor: ";    std::cin >> numero;
                    a.insertar(numero);
                }
                std::cout << '\n';
                break;
            case 2:
                if (!a.isEmpty())
                {
                    std::cout << "\nPreorden: ";    a.preorden();
                    std::cout << "\nInorden: ";     a.inorden();
                    std::cout << "\nPostorden: ";   a.postorden();
                    std::cout << '\n';
                }
                break;
            case 3:
                a.vaciar();
                break;
            case 4:
                int deleted;
                std::cout << "Ingrese Valor a Eliminar: ";  std::cin >> deleted;
                a.eliminar(deleted);
                break;
            case 5:
                if (a.isEmpty())
                    std::cout << "Esta Vacio";
                else
                    std::cout << "No Vacio";
                break;
            case 6:
                a.drawTree();
                break;
            case 7:
                std::cout << "\nCantidad de Nodos: " << a.numNodos();
                break;
            case 8:
                std::cout << "\nAltura del Arbol: " << a.altura();
                break;
            case 9:
                int buscar;
                std::cout << "Ingrese valor a buscar: ";    std::cin >> buscar;
                std::cout << a.buscar(buscar)->nodeValue();
                break;
            case 10:
                n1 = a1.newTree(nullptr, 1, nullptr);   //
                n2 = a2.newTree(nullptr, 12, nullptr);  //
                n3 = a3.newTree(n1, 10, n2);            //               100
                n1 = a1.newTree(nullptr, 51, nullptr);  //
                n2 = a2.newTree(nullptr, 70, nullptr);  //      10                   60
                n4 = a4.newTree(n1, 60, n2);            //
                n1 = a1.newTree(n3, 100, n4);           //  1       12          51          70
                a.setRoot(n1);
                break;
            case 11:
                std::cout << a.getRoot()->nodeValue();
                break;
//            case 12:
//                std::cout << n1->getLeft()->nodeValue();
        }
    } while (op != 0);

    return 0;
}