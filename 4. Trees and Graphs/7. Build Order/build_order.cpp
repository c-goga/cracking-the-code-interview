#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <stdexcept>

using namespace std;

class Project {
    public:
    char c; // identify for node
    vector<Project*> parents; // for iterating through parents to remove dependency 
                              // parents are the projects that depend on the current project
    unordered_map<Project*, bool> dependencies; // for O(1) lookup

    Project(char c) {
        this->c = c;
    }

    void addParent(Project* p) {
        parents.push_back(p);
    }

    void addDependency(Project* p) {
        dependencies[p] = true;
    }

    void removeDependency(Project* p) {
        if (dependencies[p]) dependencies.erase(p); // use erase since we check to see if the map is empty within the buildOrder function
    }
};

class BuildOrder {
    public:
    vector<Project*> buildOrder(vector<Project*> p, vector<pair<Project*, Project*>> d) {
        vector<Project*> res; // build order that will be returned

        // add all the dependencies to the projects along with the parents
        for (pair pr : d) {
            pr.second->addDependency(pr.first);
            pr.first->addParent(pr.second);
        }

        // deletion of a project from the list is considered completed, so loop until every project is completed
        while (!p.empty()) {
            bool loop = true; // used to see if a project with no dependencies is found
            for (int i = 0; i < p.size(); i++) {
                if (p[i]->dependencies.empty()) { // if no dependencies on project
                    loop = false;
                    for (Project* parent : p[i]->parents) {
                        parent->removeDependency(p[i]); // remove the dependency from the parent so future iterations can possibly complete the parent project
                    }
                    res.push_back(p[i]); // project complete, push onto build order then delete from the list
                    p.erase(p.begin() + i);
                    i--; // decrement i since the current index will hold a new element since the project was deleted
                }
            }
            // all projects have dependencies so throw error
            if (loop) throw invalid_argument("No build order can be made.");
        }
        return res;
    }
};

int main() {
    Project* a = new Project('a');
    Project* b = new Project('b');
    Project* c = new Project('c');
    Project* d = new Project('d');
    Project* e = new Project('e');
    Project* f = new Project('f');
    vector<Project*> p = {a, b, c, d, e, f};
    vector<pair<Project*, Project*>> depend = {{a, d}, {f, b}, {b, d}, {f, a}, {d, c}};
    BuildOrder bo;
    try {
        vector<Project*> res = bo.buildOrder(p, depend);
        for (int i = 0; i < res.size(); i++) {
            cout << res[i]->c << " ";
        }
        cout << endl; // e can be anywhere, f must be before a and b, a and b are interchangable and must be before d, d must be before c

        depend.push_back({c, f}); // make it invalid
        res = bo.buildOrder(p, depend); // should throw here
    } catch (exception& e) {
        cout << e.what() << endl; // No build order can be made
    }
    return 0;
}