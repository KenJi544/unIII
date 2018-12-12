import math

s = 54
so = 14
r = 0.22

ds2 = (s / so - 1) / 78

banci = {'Pacala': 0.05,
    'Tandala': 0.06,
    'Pepelea': 0.064}

def dobanda_zece_ani(so, r):
    st = 0
    c = 0
    for i in range(10):
        st += so * (1 + r + c)
        c += 0.02
    return st

prob_banca = lambda p, t: math.pow((1 + p / t),t) + 1

def choice(ban):
    t = 12
    tt = 3
    mn = None
    for k, v in ban.items():
        if mn == None:
            mn = (k, v)
        elif prob_banca(v, t) < mn[1]:
            mn = (k, v)
        t /= tt
        tt -= 1
    return mn

if __name__ == '__main__':
    print(f'ex1. t dobanda simpla = {(s / so - 1) / r}')
    print(f'ex1. t dobanda compusa = {math.log(s / so) / math.log(1 + r)}')
    print(f'ex2. {ds2}%')
    print(f'ex2. S = {so * (1 + ds2 * 100 * 78)}')
    print(f'ex2. S = {so * (1 + ds2 * 78/365)}')
    print(f'ex3. 4.04.2005-1.09.2005')
    print(f'ex3. en:{(26 + 30 + 93) / 365}')
    print(f'ex3. fr:{(26 + 30 + 93) / 360}')
    print(f'ex3. gr:{(26 + 120) / 360}')
    print(f'ex4. suma finala pe 10 ani {dobanda_zece_ani(so, r)}')
    ch = choice(banci)
    print(f'ex8. {ch[0]} este banca potrivita cu {ch[1]}%')
