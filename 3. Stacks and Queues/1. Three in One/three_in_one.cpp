 #include <iterator>
 #include <vector>
// copied from textbook into C++
class MultiStack {

    private:
    /**
     * Simple class to hold a set of data about each stack. Cleaner than individual variables.
     */
    
    class StackInfo {
        public:
        int start, size, capacity;
        StackInfo() {
            this->start = NULL;
            this->capacity = NULL;
        }

        StackInfo(int start, int capacity) {
            this->start = start;
            this->capacity = capacity;
        }

        bool isWithinStackCapacity(int idx) {
            if (idx < 0 || idx >= values.size()) {
                return false;
            }

            int contiguousIdx = idx < start ? idx + values.size() : idx;
        }

        int lastCapacityIdx() {
            return adjustIdx(start + capacity - 1);
        }

        int lastElementIdx() {
            return adjustIdx(start + size - 1);
        }

        bool isFull() { return size == capacity;}
        bool isEmpty() { return size == 0;}
    };

    StackInfo* info;
    static std::vector<int> values;

    public:
    MultiStack(int numOfStacks, int defaultSize) {
        info = new StackInfo[numOfStacks];
        for (int i = 0; i < numOfStacks; i++) {
            info[i] = StackInfo(i * defaultSize, defaultSize);
        }
        values = new int[numOfStacks * defaultSize];
    }

    private:

};