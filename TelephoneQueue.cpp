
#include <iostream>
#include <vector>
#include <queue>
#include <functional>

enum class CallType { NORMAL, EMERGENCY };

struct Call {
    int callId;
    CallType type;
    int duration; // duration in minutes
    bool callbackRequested;
};

class CircularQueue {
private:
    std::vector<Call> queue;
    int front, rear, capacity;

public:
    CircularQueue(int size) : capacity(size), front(-1), rear(-1) {
        queue.resize(capacity);
    }

    bool isFull() {
        return ((rear + 1) % capacity == front);
    }

    bool isEmpty() {
        return (front == -1);
    }

    void enqueue(const Call& call) {
        if (isFull()) {
            std::cout << "Queue Overflow! Cannot enqueue call.\n";
            return;
        }
        if (front == -1) front = 0;
        rear = (rear + 1) % capacity;
        queue[rear] = call;
        std::cout << "Enqueued Call ID: " << call.callId << "\n";
    }

    void dequeue() {
        if (isEmpty()) {
            std::cout << "Queue Underflow! Cannot dequeue call.\n";
            return;
        }
        std::cout << "Dequeued Call ID: " << queue[front].callId << "\n";
        if (front == rear) {
            front = rear = -1; // Reset queue
        }
        else {
            front = (front + 1) % capacity;
        }
    }

    void display() {
        if (isEmpty()) {
            std::cout << "Queue is empty.\n";
            return;
        }
        int i = front;
        do {
            std::cout << "Call ID: " << queue[i].callId
                << ", Type: " << (queue[i].type == CallType::NORMAL ? "NORMAL" : "EMERGENCY")
                << ", Duration: " << queue[i].duration
                << ", Callback Requested: " << (queue[i].callbackRequested ? "Yes" : "No")
                << "\n";
            i = (i + 1) % capacity;
        } while (i != (rear + 1) % capacity);
    }

    void prioritizeEmergencyCalls() {
        if (isEmpty()) return;

        std::vector<Call> tempQueue;

        // Collect emergency calls first
        for (int i = front; i <= rear; ++i) {
            if (queue[i].type == CallType::EMERGENCY) {
                tempQueue.push_back(queue[i]);
            }
        }

        // Then, collect normal calls
        for (int i = front; i <= rear; ++i) {
            if (queue[i].type == CallType::NORMAL) {
                tempQueue.push_back(queue[i]);
            }
        }

        // Rebuild the queue with emergency calls first
        for (int i = 0; i < tempQueue.size(); ++i) {
            queue[i] = tempQueue[i];
        }

        front = 0;
        rear = tempQueue.size() - 1;
    }
};

int main() {

    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";
    }



    // Happy Path Test Case 2

    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2

    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2

    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    // Happy Path Test Case 2
    {
        CircularQueue cq(4);

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        cq.dequeue();
        cq.dequeue();

        std::cout << "Queue after two dequeues:\n";
        cq.display();  std::cout << "\n\n";


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Dequeued Call ID: 2
    // Dequeued Call ID: 4
    // Queue after two dequeues:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No

    // Edge Case Test Case 2
    {
        CircularQueue cq(5);  std::cout << "\n\n";

        Call call1 = { 1, CallType::NORMAL, 10, false };
        Call call2 = { 2, CallType::EMERGENCY, 5, true };
        Call call3 = { 3, CallType::NORMAL, 15, false };
        Call call4 = { 4, CallType::EMERGENCY, 8, true };
        Call call5 = { 5, CallType::NORMAL, 20, false };

        cq.enqueue(call1);
        cq.enqueue(call2);
        cq.enqueue(call3);
        cq.enqueue(call4);
        cq.enqueue(call5);

        std::cout << "Initial Queue:\n";
        cq.display();  std::cout << "\n\n";

        cq.prioritizeEmergencyCalls();

        std::cout << "Queue after prioritizing emergency calls:\n";
        cq.display();  std::cout << "\n\n";

        // Attempt to enqueue another call to test overflow
        Call call6 = { 6, CallType::NORMAL, 12, false };
        cq.enqueue(call6); // This should trigger Queue Overflow


    }
    // Expected Output:
    // Initial Queue:
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue after prioritizing emergency calls:
    // Call ID: 2, Type: EMERGENCY, Duration: 5, Callback Requested: Yes
    // Call ID: 4, Type: EMERGENCY, Duration: 8, Callback Requested: Yes
    // Call ID: 1, Type: NORMAL, Duration: 10, Callback Requested: No
    // Call ID: 3, Type: NORMAL, Duration: 15, Callback Requested: No
    // Call ID: 5, Type: NORMAL, Duration: 20, Callback Requested: No
    // Queue Overflow! Cannot enqueue call.

    return 0;

}
