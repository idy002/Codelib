/*
后缀自动机是一种确定性有限自动机（DFA），它可以且仅可以匹配一个给定串的任意后缀。

构造一个可以接受一个给定串的所有后缀的不确定性有限自动机（NFA）是很容易的，我们发现我们用通用的将NFA转换成对应DFA的算法转换出来的DFA的状态数都很小（O(n)级别的，远远达不到指数级别）。于是，人们就开始研究这种特殊的NFA，并提出了在线增量算法，用O(n)的时间复杂度构造该NFA的DFA。在转换过程中，DFA中对应的NFA中的状态集合其实就是我们的right集合。——————以上在胡扯———————

后缀自动机的增量算法：
*/
struct Sam {
    int son[S][26], val[S], pnt[S], ntot, last;
    Sam() { pnt[0] = -1; }
    void append( int c ) {
        int p = last;
        int np = ++ntot;
        val[np] = val[p]+1;
        while( p!=-1 && !son[p][c] ) 
            son[p][c]=np, p=pnt[p];
        if( p==-1 ) {
            pnt[np] = 0;
        } else {
            int q=son[p][c];
            if( val[q]==val[p]+1 ) {
                pnt[np] = q;
            } else {
                int nq = ++ntot;
                memcpy( son[nq], son[q], sizeof(son[nq]) );
                val[nq] = val[p]+1;
                pnt[nq] = pnt[q];
                pnt[q] = pnt[np] = nq;
                while( p!=-1 && son[p][c]==q )
                    son[p][c]=nq, p=pnt[p];
            }
        }
        last = np;
    }
};
/*
后缀自动机构造完成之后，我们得到了4个东西：转移DAG，Parent树，每个点的right集合，
每个点的字符串集合的长度区间。（其中最后一个可以由地一个DP出来）

转移DAG最直接的用处是子串判定问题，因为它将原串的所有子串唯一的映射到了该DAG上的某个节点，
并且将该子串放到DAG上跑，会跑到该节点。每个节点可能代表多个串。

可以在DAG上进行DP，得出从某点开始最多匹配多少个本质不同的子串，如果再加上right集合，
就可以算出普通字串个数（位置不同本质相同也算）。

转移DAG加上Parent树可以提供给我们访问原串某个子串的所有子串的能力。

对于处理多个串的问题，我们可以先用分割符连接各个串，然后构造后缀自动机，并且重新定义一个点代表的字串：
原本的串去除带有分割符的串，我们可以DP算出每个节点代表的串的数量以及长度区间。
这样可以通过刚才访问子串的子串的方法访问一个串的所有子串。
*/
