// RedBlackTree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
#include <vector>
#include"RBTree.h"                                                                         
#include <set>
#include <unordered_set>
#include <ctime> 
#include <new.h>
using namespace std; 
 

#define TEST_RULE_CODE
void testTree();
int main()
{
    testTree();
    return 0;  
}
void testTree(){ 
    int k =5;
    ptrdiff_t t; 
    void* ptr = nullptr;
    t = time(&t);

    while(k--){
        RBTree rbt; 
        vector<int> vec;
                                           

        //vector<int> vec{ 69,5,31,42,98,88,0,64,97,33,86,22,90,26,28,9,45,91,25,55,59,70,6,68,2,66,17,56,46,21,85,80,82,75,11,99,35,76,63,58,67,37,32,8,1,87,23,93,54,52 };
        int total = 50; 
        for (int i = 0; i < total; ) {
            int m;
            if (1) {
                int num = (t % 100 + rand()) % 100; 
                m = num;
            }
            else m = vec[i];
            vec.emplace_back(m);

            cout << m << " ";
            i++;
        }
        cout << "#" << endl;

        for (auto m : vec) {
            rbt.insert(m);
        #ifdef TEST_RULE_CODE
            printf(" insert num=%d\n", m);
            printf("rule1,rule2,rule3:%d %d %d size=%d\n",
                rbt.checkRule1(), rbt.checkRule2(rbt.root), rbt.checkRule3(rbt.root), rbt.size);
        #endif // TEST_RULE_CODE

        }

        rbt.printByInOrder();
        int k = 0;
        for (auto num : vec) {
            bool res = rbt.remove(num);
#ifdef TEST_RULE_CODE
            bool c1 = rbt.checkRule1(), c2 = rbt.checkRule2(rbt.root), c3 = rbt.checkRule3(rbt.root);
            printf(" isDeleteOk[%d],num=%d\n", res, num);
            printf("rule1,rule2,rule3:%d %d %d size=%d\n", c1, c2, c3, rbt.size);
            if (!(c1 && c2 && c3))cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
#endif // 
           
            
            if (++k > total - 3)break;
        }
        cout << "after delete:" << endl;
        rbt.printByInOrder();  
    }

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
