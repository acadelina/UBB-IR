def merge_sort(iterable, key=None, key2 = None, cmp=None, reverse=False):
    """
    Functie recursiva care sorteaza o lista
    preconditii: iterable: list
                 key: functie dupa care se sorteaza
                 key2: functie dupa care se sorteaza
                 cmp: compararea
                 reverse: ordonare crescatoare/descreascatoare
    postconditii: lista ordonata
    """
    if key is None:
        key = lambda x: x
    if key2 is None:
        key2 = lambda x: x
    if cmp is None:
        cmp = lambda a, b: a > b

    iterable = list(iterable)

    if reverse:
        cmp = lambda a, b: a < b

    if len(iterable) <= 1:
        return iterable

    middle = len(iterable) // 2
    left = merge_sort(iterable[:middle], key=key, key2 = key2, cmp=cmp, reverse=reverse)
    right = merge_sort(iterable[middle:], key=key, key2 = key2, cmp=cmp, reverse=reverse)

    return merge(left, right, key=key, key2 = key2, cmp=cmp)

def merge(left, right, key,key2, cmp):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if cmp(key(left[i]), key(right[j])) < 0 or (cmp(key2(left[i]),key2(right[j]))<=0 and cmp(key(left[i]), key(right[j])) ==0):
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result += left[i:]
    result += right[j:]
    return result

def bingoSort(iterable, key=None, cmp=None, reverse=False):
    """
    Functie care sorteaza o lista de elemente cu metoda bingo
    preconditii:iterable: list
                 key: functie dupa care se sorteaza
                 cmp: compararea
                 reverse: ordonare crescatoare/descreascatoare
    postconditii: lista ordonata
    Complexitate:
    n-numar elemente
    m-numar elemente distincte
    -caz favorabil(toate elementele identice):O(n)
    -caz nefavorabil(toate elementele distincte): O(n*m)
    -caz mediu: O(n*n)
    """
    if key is None:
        key = lambda x: x
    if cmp is None:
        cmp = lambda a, b: a > b
    if reverse:
        cmp = lambda a, b: a < b
    iterable = list(iterable)
    size = len(iterable)

    bingo = min(iterable, key=key)
    #print(bingo)
    largest = max(iterable, key=key)
    #print(largest)
    nextBingo = largest
    nextPos = 0
    while key(bingo)<key(nextBingo):
        #print(key(bingo))

        startPos = nextPos
        for i in range(startPos, size):
            
            if cmp(key(iterable[i]),key(bingo))==0:
                iterable[i], iterable[nextPos] = iterable[nextPos], iterable[i]
                nextPos += 1
            elif cmp(key(iterable[i]),key(nextBingo))<0:
                nextBingo = iterable[i]
                
        #print(key(nextBingo))       
        bingo = nextBingo
        nextBingo = largest
        

    return iterable

def test_mergesort():
    l=[1,4,7,9,2,1,4,5]
    assert merge_sort(l,key=lambda x:x)==[1,1,2,4,4,5,7,9]

    assert merge_sort(l,key=lambda x:x,reverse=True)==[9,7,5,4,4,2,1,1]

    assert merge_sort(l,cmp=lambda a, b: a < b)==[9,7,5,4,4,2,1,1]

def test_bingo():
    l=[1,4,7,9,2,1,4,5]
    assert bingoSort(l,key=lambda x:x)==[1,1,2,4,4,5,7,9]

    assert bingoSort(l,key=lambda x:x,reverse=True)==[9,7,5,4,4,2,1,1]

    assert bingoSort(l,cmp=lambda a, b: a < b)==[9,7,5,4,4,2,1,1]


test_mergesort()