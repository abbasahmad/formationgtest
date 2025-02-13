#include "gtest/gtest.h"


//APRES AVOIR COMPLETER LE FICHIER, On VA FAIRE LA SUITE SETUP ET TEARDOWN ENSEMBLE

// Classe que nous voulons tester
template <typename E>  // E est le type élément.
class Queue {
private:
    std::vector<E> _v;

public:
    Queue() {}
    ~Queue() {
        std::cout << "Queue destructor." << std::endl;
    }
    void Enqueue(const E& element) {
        _v.push_back(element);
    }
    // Throws si la file d'attente est vide.
    E Dequeue() {
        if (IsEmpty()) {
            throw;
        }
        auto tmp = _v[0];
        _v.erase(_v.begin());
        return tmp;
    }
    size_t size() const {
        return _v.size();
    }
    bool IsEmpty() {
        return _v.empty();
    }
};

// Class pour la fixture
class QueueTest : public ::testing::Test {
protected:

    //PRE CONDITIONS , SETUP, BEFORE
    void SetUp() override {
        start_time_ = std::chrono::high_resolution_clock::now(); //HORLOGE DEBUT
        
        q_.Enqueue(1);
        q_.Enqueue(2);
    }

    void TearDown() override {

        //Calcult de la duration du test
        auto end_time_ms = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_ms - start_time_);

        std::cout << "Test took: " << duration.count() << " ms" << std::endl;

        //VERIFIER QUE LE TEST NE DEPASSE PAS 1000 ms en temps d'execution
        //....

        PrintQueue();
        std::cout << "=========================Fin du test!=========================" << std::endl;
    }

    void PrintQueue() {
        if (q_.IsEmpty()) {
            std::cout << "-> The queue is empty." << std::endl;
        }
        else {
            while (!q_.IsEmpty()) {
                std::cout << "-> Remaining item in the queue q_.Dequeue(): " << q_.Dequeue() << std::endl;
            }
        }
    }

    Queue<int> q_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
};


// Lorsque vous disposez d'une fixture de test, vous définissez un test à l'aide de TEST_F au lieux de TEST
TEST_F(QueueTest, SizeAndEmptyWork) {
    EXPECT_EQ(q_.size(), 2);
    EXPECT_FALSE(q_.IsEmpty());
}

//Creer des test pour verifier que le Dequeue et Enqueue fonctionnent
//...


//Creer un test qui fait en sorte de mettre top de temps a tourner "TakesTooLong"
//....

