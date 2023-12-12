//╔╗──╔══╗╔══╗╔════╗╔══╗╔══╗╔╗╔╗╔═══╗╔╗╔══╗
//║║──╚╗╔╝║╔═╝╚═╗╔═╝║╔╗║║╔═╝║║║║║╔══╝║║║╔═╝
//║║───║║─║╚═╗──║║──║║║║║║──║╚╝║║╚══╗║╚╝║
//║║───║║─╚═╗║──║║──║║║║║║──║╔╗║║╔══╝║╔╗║
//║╚═╗╔╝╚╗╔═╝║──║║──║╚╝║║╚═╗║║║║║╚══╗║║║╚═╗
//╚══╝╚══╝╚══╝──╚╝──╚══╝╚══╝╚╝╚╝╚═══╝╚╝╚══╝
//╔══╗╔══╗╔═══╗╔═══╗╔╗╔╗╔═══╗╔═══╗
//║╔═╝║╔╗║║╔═╗║║╔══╝║║║║║╔══╝║╔═╗║
//║╚═╗║║║║║╚═╝║║╚══╗║║║║║╚══╗║╚═╝║
//║╔═╝║║║║║╔╗╔╝║╔══╝║╚╝║║╔══╝║╔╗╔╝
//║║──║╚╝║║║║║─║╚══╗╚╗╔╝║╚══╗║║║║
//╚╝──╚══╝╚╝╚╝─╚═══╝─╚╝─╚═══╝╚╝╚╝

#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node *next;
    Node *prev;
    Node *child;
    Node *parent;
    int degree;
    bool flag;
};

struct Fib_Heap {
    int size;
    Node* heap;

public:

    Fib_Heap(){
        heap = nullptr;
        size = 0;
    }

    Fib_Heap(Fib_Heap& heapchik) {
        heap = make_copy_heap(heapchik);
        size = heapchik.size;
    }

    Fib_Heap(Fib_Heap &first_heapchik, Fib_Heap &second_heapchik) {
        Node *first = make_copy_heap(first_heapchik);
        Node *second = make_copy_heap(second_heapchik);
        if (first == nullptr) {
            heap = second;
            size = second_heapchik.size;
        }
        else if (second == nullptr) {
            heap = first;
            size = first_heapchik.size;
        }
        else {
            if (first->key > second->key) {
                Node *temp = first;
                first = second;
                second = temp;
            }
            Node *for_first_node = first->next;
            Node *for_second_node = second->prev;
            first->next = second;
            second->prev = first;
            for_first_node->prev = for_second_node;
            for_second_node->next = for_first_node;
            heap = first;
            size = first_heapchik.size + second_heapchik.size;
        }
    }

    Node* make_copy_heap(Fib_Heap& heapchik) {
        if (heapchik.heap != nullptr) {
            Node *copy_of_old_heap = new Node;
            copy_of_old_heap->key = heapchik.heap->key;
            copy_of_old_heap->flag = heapchik.heap->flag;
            copy_of_old_heap->degree = heapchik.heap->degree;
            copy_of_old_heap->parent = nullptr;
            copy_of_old_heap->child = copy_child(heapchik.heap->child,copy_of_old_heap);
            copy_level(heapchik.heap, heapchik.heap->next, copy_of_old_heap, copy_of_old_heap);

            return copy_of_old_heap;
        }
        else {
            return nullptr;
        }
    }


    void insert(int key) {
        Node *new_Node = new Node;
        ++size;
        new_Node->key = key;
        new_Node->next = new_Node;
        new_Node->prev = new_Node;
        new_Node->degree = 0;
        new_Node->flag = false;
        new_Node->child = nullptr;
        new_Node->parent = nullptr;

        if (heap == nullptr) {
            heap = new_Node;
        }
        else {
            if (heap->key > new_Node->key) {
                swap(heap, new_Node);
            }
            Node *for_first_node = heap->next;
            Node *for_second_node = new_Node->prev;
            heap->next = new_Node;
            new_Node->prev = heap;
            for_first_node->prev = for_second_node;
            for_second_node->next = for_first_node;
        }
    }

    int extract_min() {
        if (size == 0) {
            return 42;
        } else {
            Node* node = heap;
            if (heap->child != nullptr) {
                Node *child_node = heap->child;
                do {
                    child_node->flag = false;
                    child_node->parent = nullptr;
                    child_node = child_node->next;
                } while (child_node != heap->child);
            }

            if (heap->next == heap) {
                heap = heap->child;
            } else {
                heap->next->prev = heap->prev;
                heap->prev->next = heap->next;
                if (heap->next == nullptr) {
                    heap = heap->child;
                }
                else if (heap->child == nullptr) {
                    heap = heap->next;
                } else {
                    if (heap->next->key > heap->child->key) {
                        swap(heap->next, heap->child);
                    }
                    Node* for_first_node = heap->next->next;
                    Node* for_second_node = heap->child->prev;
                    heap->next->next = heap->child;
                    heap->child->prev = heap->next;
                    for_first_node->prev = for_second_node;
                    for_second_node->next = for_first_node;
                }
            }

            consolidate(node);

            int ret = node->key;
            delete node;
            --size;
            return ret;
        }
    }

    void decrease_key(Node *node, int key) {
        if (node == nullptr) {
            return;
        }


        node->key = key;
        if (node->parent) {
            if (node->key < node->parent->key) {
                heap = cut(heap, node);
                Node *parent = node->parent;
                node->parent = nullptr;
                while (parent != nullptr && parent->flag) {
                    heap = cut(heap, parent);
                    node = parent;
                    parent = node->parent;
                    node->parent = nullptr;
                }
                if (parent != nullptr && parent->parent != nullptr) {
                    parent->flag = true;
                }
            }
        } else {
            if (node->key < heap->key) {
                heap = node;
            }
        }
    }

    Node* find_node_with_element(Node *node, int key) {
        Node *n = node;
        if (n == nullptr) {
            return nullptr;
        }
        do {
            if (n->key == key) {
                return n;
            }

            Node *ret = find_node_with_element(n->child, key);

            if (ret != nullptr) {
                return ret;
            }
            n = n->next;
        } while (n != heap);

        return nullptr;
    }

private:

    void consolidate(Node* node) {
        if (heap != nullptr) {
            Node* mas_of_trees[] = {nullptr};

            bool mark = true;

            while (mark) {
                if (mas_of_trees[heap->degree] != nullptr) {
                    Node *tree = mas_of_trees[node->degree];
                    if (tree == node) {
                        break;
                    }
                    if (heap->key < tree->key) {
                        tree->prev->next = tree->next;
                        tree->next->prev = tree->prev;
                        add_child(heap, tree);
                    } else {
                        tree->prev->next = tree->next;
                        tree->next->prev = tree->prev;
                        if (heap->next == heap) {
                            tree->next = tree;
                            tree->prev = tree;
                            add_child(tree, heap);
                            heap = tree;
                        } else {
                            heap = tree;
                            heap = tree;
                            tree->next = heap->next;
                            tree->prev = heap->prev;
                            add_child(tree, heap);
                            heap = tree;
                        }
                    }
                } else {
                    mas_of_trees[heap->degree] = node;
                }
                heap = heap->next;
            }
            Node *min = heap;
            Node *start = heap;
            do {
                if (heap->key < min->key)min = heap;
                heap = heap->next;
            } while (heap != start);
            heap = min;
        }
    }

    void add_child(Node *parent, Node *child_for_parent) {
        child_for_parent->prev = child_for_parent;
        child_for_parent->next = child_for_parent;

        child_for_parent->parent = parent;
        ++parent->degree;
        if (parent->child == nullptr) {
            parent->child = child_for_parent;
        }
        else {
            swap(parent->child, child_for_parent);
        }
        Node *for_first_node = parent->child->next;
        Node *for_second_node = child_for_parent->prev;
        parent->child->next = child_for_parent;
        child_for_parent->prev = parent->child;
        for_first_node->prev = for_second_node;
        for_second_node->next = for_first_node;
    }
    Node* cut(Node *heapchik, Node *node) {
        if (node->next == node) {
            node->parent->child = nullptr;
        }
        else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
            node->parent->child = node->next;
        }
        node->next = node;
        node->prev = node;
        node->flag = false;
        if (heapchik == nullptr) {
            return node;
        }
        if (heapchik->key > node->key) {
            swap(heapchik, node);
        }
        Node *for_first_node = heapchik->next;
        Node *for_second_node = node->prev;
        heapchik->next = node;
        node->prev = heap;
        for_first_node->prev = for_second_node;
        for_second_node->next = for_first_node;

        return heapchik;
    }

    void copy_level(Node *need_to_copy_begin_of_the_level, Node *need_to_copy_after_begin_of_the_level, Node *copy_start_of_layer, Node *future_new_node_next) {
        if (need_to_copy_begin_of_the_level != need_to_copy_after_begin_of_the_level) {

            Node *new_node_next = new Node;

            new_node_next->key = need_to_copy_after_begin_of_the_level->key;
            new_node_next->flag = need_to_copy_after_begin_of_the_level->flag;
            new_node_next->degree = need_to_copy_after_begin_of_the_level->degree;
            new_node_next->parent = future_new_node_next->parent;
            new_node_next->prev = future_new_node_next;
            future_new_node_next->next = new_node_next;
            new_node_next->child = copy_child(need_to_copy_after_begin_of_the_level->child,new_node_next);
            copy_level(need_to_copy_begin_of_the_level, need_to_copy_after_begin_of_the_level->next, copy_start_of_layer, new_node_next);
        }

        else {
            copy_start_of_layer->prev = future_new_node_next;
            future_new_node_next->next = copy_start_of_layer;
            return;
        }
    }

    Node* copy_child(Node* need_to_copy_child, Node* future_parent) {
        if (need_to_copy_child != nullptr) {
            Node *new_child_node = new Node;

            new_child_node->key = need_to_copy_child->key;
            new_child_node->flag = need_to_copy_child->flag;
            new_child_node->degree = need_to_copy_child->degree;
            new_child_node->parent = future_parent;
            new_child_node->child = copy_child( need_to_copy_child->child,new_child_node);
            copy_level(need_to_copy_child, need_to_copy_child->next, new_child_node, new_child_node);

            return need_to_copy_child;
        }
        else {
            return nullptr;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<Fib_Heap> vectorchik(1000000);
    string command;
    int count = 0;
    while (cin >> command) {
        if (command == "end") {
            break;
        }
        if (command == "create") {
            Fib_Heap new_mas;
            vectorchik[count] = new_mas;
            ++count;
        } else if (command == "insert") {
            int k = 0, x = 0;
            cin >> k >> x;
            vectorchik[k].insert(x);
        } else if (command == "extract-min") {
            int k = 0;
            cin >> k;
            int ans = vectorchik[k].extract_min();
            if (ans == 42) {
                cout << "*" << '\n';
            } else {
                cout << ans << '\n';
            }
        } else if (command == "merge") {
            int k = 0, m = 0;
            cin >> k >> m;
            Fib_Heap new_heap(vectorchik[k], vectorchik[m]);
            vectorchik[count] = new_heap;
            ++count;
        } else if (command == "decrease-key") {
            int k = 0, x = 0, y = 0;
            Node* find_uzel;
            cin >> k >> x >> y;
            find_uzel = vectorchik[k].find_node_with_element(vectorchik[k].heap, x);
            if (find_uzel != nullptr) {
                vectorchik[k].decrease_key(find_uzel, y);
            }
        }
    }
    return 0;
}