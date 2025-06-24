#include <iostream>
#include <vector>

// Definition for singly-linked list, as provided by LeetCode.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    /**
     * @brief Adds two numbers represented by linked lists.
     *
     * The digits are stored in reverse order in the linked lists. This function
     * iterates through both lists simultaneously, adding the digits along with
     * a carry-over from the previous sum. A new linked list is constructed to
     * represent the sum.
     *
     * A dummy head node is used to simplify the logic for building the result list.
     * The loop continues as long as there are digits to process in either list or
     * a final carry exists.
     *
     * @param l1 The head of the first linked list.
     * @param l2 The head of the second linked list.
     * @return The head of the resulting linked list representing the sum.
     */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Dummy head helps in simplifying the insertion of the first node.
        ListNode* dummyHead = new ListNode(0);
        ListNode* current = dummyHead;
        int carry = 0;

        // Loop until both lists are fully traversed and there's no carry left.
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            // Get the value from the current node of l1, or 0 if l1 is null.
            int val1 = (l1 != nullptr) ? l1->val : 0;
            // Get the value from the current node of l2, or 0 if l2 is null.
            int val2 = (l2 != nullptr) ? l2->val : 0;

            // Calculate the sum of digits and the carry.
            int sum = val1 + val2 + carry;
            carry = sum / 10;
            int newDigit = sum % 10;

            // Create a new node with the calculated digit and append it.
            current->next = new ListNode(newDigit);
            current = current->next;

            // Move to the next node in l1 if it exists.
            if (l1 != nullptr) {
                l1 = l1->next;
            }
            // Move to the next node in l2 if it exists.
            if (l2 != nullptr) {
                l2 = l2->next;
            }
        }

        // The result list starts from the node after the dummy head.
        ListNode* resultHead = dummyHead->next;
        delete dummyHead; // Free the memory of the dummy head.
        return resultHead;
    }
};

// Helper function to create a linked list from a vector
ListNode* createLinkedList(const std::vector<int>& vec) {
    if (vec.empty()) return nullptr;
    ListNode* head = new ListNode(vec[0]);
    ListNode* current = head;
    for (size_t i = 1; i < vec.size(); ++i) {
        current->next = new ListNode(vec[i]);
        current = current->next;
    }
    return head;
}

// Helper function to print a linked list
void printLinkedList(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "nullptr" << std::endl;
}

// --- Example Usage ---
int main() {
    Solution sol;

    // Example 1: l1 = [2,4,3], l2 = [5,6,4] -> [7,0,8]
    ListNode* l1 = createLinkedList({2, 4, 3});
    ListNode* l2 = createLinkedList({5, 6, 4});
    std::cout << "Input 1: "; printLinkedList(l1);
    std::cout << "Input 2: "; printLinkedList(l2);
    ListNode* result = sol.addTwoNumbers(l1, l2);
    std::cout << "Output:  "; printLinkedList(result);
    std::cout << std::endl;

    // Example 2: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9] -> [8,9,9,9,0,0,0,1]
    ListNode* l3 = createLinkedList({9,9,9,9,9,9,9});
    ListNode* l4 = createLinkedList({9,9,9,9});
    std::cout << "Input 1: "; printLinkedList(l3);
    std::cout << "Input 2: "; printLinkedList(l4);
    ListNode* result2 = sol.addTwoNumbers(l3, l4);
    std::cout << "Output:  "; printLinkedList(result2);
    std::cout << std::endl;
    
    return 0;
}
