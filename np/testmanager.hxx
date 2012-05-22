#ifndef __NP_TESTMANAGER_H__
#define __NP_TESTMANAGER_H__ 1

#include "np/util/common.hxx"
#include "np/types.hxx"
#include "np/testnode.hxx"
#include <string>
#include <vector>

namespace spiegel { namespace dwarf { class state_t; } }

namespace np {

class classifier_t;

class testmanager_t
{
public:
    /* testmanager is a singleton */
    static testmanager_t *instance();

    testnode_t *find_node(const char *nm) const
    {
	return root_ ? root_->find(nm) : 0;
    }
    testnode_t *get_root() { return root_; }

    static void done() { delete instance_; }
private:
    static void *operator new(size_t sz) { return xmalloc(sz); }
    static void operator delete(void *x) { free(x); }
    testmanager_t();
    ~testmanager_t();

    functype_t classify_function(const char *func, char *match_return, size_t maxmatch);
    void add_classifier(const char *re, bool case_sensitive, functype_t type);
    void setup_classifiers();
    spiegel::function_t *find_mock_target(std::string name);
    void discover_functions();
    void setup_builtin_intercepts();

    static testmanager_t *instance_;

    std::vector<classifier_t*> classifiers_;
    spiegel::dwarf::state_t *spiegel_;
    testnode_t *root_;
    testnode_t *common_;	// nodes from filesystem root down to root_
};

// close the namespace
};

#endif /* __NP_TESTMANAGER_H__ */