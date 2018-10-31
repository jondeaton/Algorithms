"""
Alien Alphabet

Given a list of $n$ words which have been sorted lexicographically by some
arbitrary alphabet of length $k$, return the lexicographic order of the
characters in the alphabet. For example if you were given the list of words

\begin{center}
\tt{["za", "cba", "caa", "ba"]}
\end{center}

The alphabet which sorted these words is: \verb|"zcba"|. It is guaranteed
that there is sufficient information from the ordering of the words derive
 the order for every character in the alphabet. \\


\textbf{Hint:} Create a graph where characters are vertices!

\begin{mdframed}
If we create a graph with each character of the alphabet being a vertex, and
draw edges between vertices $u$ and $v$ if $u$ comes before $v$ in the alphabet,
then we can find the order of characters in the alphabet by topologically
sorting this graph. The problem is then reduced to determining which edges
to add to the graph. Let word $A$ come before word $B$ in the word list, and
let $a$ and $b$ be the first characters of $A$ and $B$ which differ at
position $i$ in the words. Since the words are sorted, we can conclude that
letter $a$ comes before $b$ in the alphabet. We cannot conclude anything else
about the order based on $A$ and $B$ alone.
Therefore, we can construct our graph by iterating through each pair of
adjacent words in the list adding an edge between the two characters which
differ in the pair. Note we need not iterate through every pair because
non-adjacent word pairs will add edges with redundant order information.

To analyze running time, note that it takes time $O(k + n)$ time to build the
graph, and $O(k + n)$ time to topologically sort the graph  (since there are
$k$ vertexes and $n$ edges, and we use DFS), then the overall running time
is $O(k + n)$.
"""


def find_alpabet(words):
    graph = make_graph(words)
    return topo_sort(graph)

def make_graph(words):
    characters = set()
    for word in words:
        characters.update(set(word))
    characters = list(characters)

    # adjacency list
    graph = {char: list() for char in characters}
    for i in range(len(words) - 1):
        word_A = words[i]
        word_B = words[i + 1]
        add_edge(graph, word_A, word_B)
    return graph

def add_edge(graph, word_A, word_B):
    n = min(len(word_A), len(word_B))
    for i in range(n):
        if word_A[i] != word_B[i]:
            graph[word_A[i]] = word_B[i]
            return

def topo_sort(graph):
    n = len(graph)
    visited = {char: False for char in graph}

    # DFS from each starting node
    order = list()
    for char in graph:
        if visited[char]: continue
        dfs(graph, char, visited, order)

    # reverse because we "appended" to "order" in DFS
    return str(list(reversed(order)))

def dfs(graph, char, visited, order):
    visited[char] = True
    for c in graph[char]:
        if visited[c]: continue
        dfs(graph, c, visited, order)
    order.append(char)
