#ifndef PRIORITY_HPP
#define PRIORITY_HPP

#include <string>
#include <stdexcept>

using namespace std;

class Priority {
        private:
                string priority;
                void validade(string priority);

        public:
                void set(string priority);
                string get();

};

#endif
