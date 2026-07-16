#include "TransactionList.h"
#include <iostream> 

TransactionList::TransactionList() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}


TransactionList::~TransactionList() {
	Node* curr = head;
	while (curr) {
		Node* next = curr->next;
		delete curr;
		curr = next;
	}
}


TransactionList::TransactionList(const TransactionList& other) {
	head = nullptr;
	tail = nullptr;
	size = 0;


	Node *current = other.head;

	while (current != nullptr) {
		if (current->data.type == Transaction::DEPOSIT) deposit(current->data.dollars, current->data.account_number);
		else if (current->data.type == Transaction::WITHDRAWAL) withdraw(current->data.dollars, current->data.account_number);
		else if (current->data.type == Transaction::TRANSFER) transfer(current->data.dollars, current->data.account_number, current->data.to_acct);
		current = current->next;
	}
}


TransactionList& TransactionList::operator=(const TransactionList& other) {
	if (this == &other) return *this;

	Node *current = head;
	while (current != nullptr) {
	       Node* nextNode = current ->next;
	       delete current;
	       current = nextNode;
	}
	head = tail = nullptr;
	size = 0;

	Node* temp = other.head;
	while (temp != nullptr) {
		if (temp->data.type == Transaction::DEPOSIT) deposit(temp->data.dollars, temp->data.account_number);
		else if (temp->data.type == Transaction::WITHDRAWAL) withdraw(temp->data.dollars, temp->data.account_number);
		else if (temp->data.type == Transaction::TRANSFER) transfer(temp->data.dollars, temp->data.account_number, temp->data.to_acct);
		temp = temp->next;
	}
	return *this;
}

Transaction* TransactionList::getFirst() {
	if (!head) return nullptr;
	return &head->data;
}

Transaction* TransactionList::getNext(Transaction* current) {
	Node* node = head;
	while (node) {
     		if (&node->data == current) {
          		if (node->next)
               	 	return &node->next->data;
            		return nullptr;
        	}
        	node = node->next;
    	}	
    	return nullptr;
}


bool TransactionList::remove(Transaction* t) {
    	Node* curr = head;

    	while (curr != nullptr) {
        	if (&curr->data == t) {

            	if (curr->prev)
                	curr->prev->next = curr->next;
            	else
                	head = curr->next;

            	if (curr->next)
                	curr->next->prev = curr->prev;
            	else
                	tail = curr->prev;

            	delete curr;
            	size--;
            	return true;
        	}

        	curr = curr->next;
    	}

    	return false;
}


int TransactionList::length() const {
	return size;
}

bool TransactionList::deposit(int dollars, unsigned int account_number) {
	Transaction t(Transaction::DEPOSIT, dollars, account_number);
	Node *newNode = new Node(t);

	if (head == nullptr) head = tail = newNode;
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	size++;
	return true;
}



bool TransactionList::withdraw(int dollars, unsigned int account_number) {
	Transaction t(Transaction::WITHDRAWAL, dollars, account_number);
	Node* newNode = new Node(t);

	if (head == nullptr) head = tail = newNode;
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	size++;
	return true;
}


bool TransactionList::transfer(int dollars, unsigned int from_acct, unsigned int to_acct) {
	Transaction t(Transaction::TRANSFER, dollars, from_acct, to_acct);
	Node* newNode = new Node(t);

	if (head == nullptr) head = tail = newNode;
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	size++;
	return true;
}


TransactionList& TransactionList::operator+=(TransactionList& other) {
	if (this == &other || other.head == nullptr) return *this;

	if (this->head == nullptr) {
		this->head = other.head;
		this->tail = other.tail;
	}
	else {
		this->tail->next = other.head;
		other.head->prev = this->tail;
		this->tail = other.tail;
	}

	this->size += other.size;
	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;

	return *this;
}



int TransactionList::collapse() {

    	if (head == nullptr) return 0;

    	Node* curr = head;

    	while (curr != nullptr) {
        	if (curr->data.type == Transaction::TRANSFER) {

            	int amt = curr->data.dollars;
            	unsigned int from = curr->data.account_number;
            	unsigned int to = curr->data.to_acct;

            	Node* nextNode = curr->next;

        
            	curr->data.type = Transaction::WITHDRAWAL;
            	curr->data.account_number = from;

     
           	Transaction t(Transaction::DEPOSIT, amt, to);
            	Node* newNode = new Node(t);

            	newNode->next = curr->next;
            	newNode->prev = curr;

            	if (curr->next)
                	curr->next->prev = newNode;
            	else
                	tail = newNode;

            	curr->next = newNode;
            	size++;

            	curr = nextNode;
        	}
        	else {
            	curr = curr->next;
        	}
    	}


    	int distinct = 0;
    	curr = head;

    	while (curr != nullptr) {
        	int net = (curr->data.type == Transaction::DEPOSIT) ? curr->data.dollars : -curr->data.dollars;
        	Node* rm = curr->next;
        	while (rm != nullptr) {
            	Node* nRm = rm->next;
            	if (rm->data.account_number == curr->data.account_number) {
                	if (rm->data.type == Transaction::DEPOSIT)
                    	net += rm->data.dollars;
                	else net -= rm->data.dollars;

                
                	if (rm->prev) rm->prev->next = rm->next;
                	if (rm->next) rm->next->prev = rm->prev;
                	if (rm == tail) tail = rm->prev;

                	delete rm;
                	size--;
            	}

           	rm = nRm;
        	}

        	if (net >= 0) {
            	curr->data.type = Transaction::DEPOSIT;
            	curr->data.dollars = net;
        	}
        	else {
            	curr->data.type = Transaction::WITHDRAWAL;
            	curr->data.dollars = -net;
        	}

        	distinct++;
        	curr = curr->next;
    	}

    	return distinct;
}




int TransactionList::sort(std::string key) {
	if (key != "account_number" && key != "transaction_type" && key != "dollars") {
		return -1;
	}

	if(size <2) {
		return 0;
	}
	
	int swaps = 0;
	bool swapped;


	do {
		swapped = false;
		Node *curr = head;

		while (curr != nullptr && curr->next != nullptr) {
			bool to_swap = false;
			Node *A = curr;
			Node *B = curr->next;

			if (key == "account_number") {
				if (A->data.account_number > B->data.account_number) to_swap = true;
			}
			else if (key == "dollars") {
				if (A->data.dollars > B->data.dollars) to_swap = true;
			}
			else if (key == "transaction_type") {
				if (A->data.type > B->data.type) to_swap = true;
			}
			
			

			if(to_swap) {
				Node* bA = A->prev;
				Node* aB = B->next;

			
				if (bA != nullptr) {
					bA->next = B;
				}
				else {
					head = B;
				}


				if (aB != nullptr) {
					aB->prev = A;
				}
				else {
					tail = A;
				}


				B->next = A;			
				A->next = aB;

				A->prev = B;
				B->prev = bA;

				swaps++;
				swapped = true;

				curr= B->next;
			}
			else {
				curr = curr->next;
			}
		}
	} while (swapped);
	
	return swaps;
}






std::ostream& operator<<(std::ostream& os, const TransactionList& list) {
	TransactionList::Node *curr = list.head;
	while (curr != nullptr) {
		std::string tS;
		if (curr->data.type == Transaction::DEPOSIT) tS = "Deposit";
		else if (curr->data.type == Transaction::WITHDRAWAL) tS = "Withdraw";
		else if (curr->data.type == Transaction::TRANSFER) tS = "Transfer";

		os << tS << " $" << curr->data.dollars << " " << curr->data.account_number;
		if (curr->data.type == Transaction::TRANSFER) {
			os << " " << curr->data.to_acct;
		}
		os << std::endl;
		curr = curr->next;
	}
	return os;
}


