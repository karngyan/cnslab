'''
Author: @karngyan
DSA Implementation
'''
from random import randrange
from hashlib import sha1
from gmpy2 import xmpz, to_binary, invert, powmod, is_prime


def generate_p_q(L, N):
    g = N  # g >= 160
    n = (L - 1) // g
    b = (L - 1) % g
    while True:
        # generate q
        while True:
            s = xmpz(randrange(1, 2 ** (g)))
            a = sha1(to_binary(s)).hexdigest()
            zz = xmpz((s + 1) % (2 ** g))
            z = sha1(to_binary(zz)).hexdigest()
            U = int(a, 16) ^ int(z, 16)
            mask = 2 ** (N - 1) + 1
            q = U | mask
            if is_prime(q, 20):
                break
        # generate p
        i = 0  # counter
        j = 2  # offset
        while i < 4096:
            V = []
            for k in range(n + 1):
                arg = xmpz((s + j + k) % (2 ** g))
                zzv = sha1(to_binary(arg)).hexdigest()
                V.append(int(zzv, 16))
            W = 0
            for qq in range(0, n):
                W += V[qq] * 2 ** (160 * qq)
            W += (V[n] % 2 ** b) * 2 ** (160 * n)
            X = W + 2 ** (L - 1)
            c = X % (2 * q)
            p = X - c + 1  # p = X - (c - 1)
            if p >= 2 ** (L - 1):
                if is_prime(p, 10):
                    return p, q
            i += 1
            j += n + 1


def generate_g(p, q):
    while True:
        h = randrange(2, p - 1)
        exp = xmpz((p - 1) // q)
        g = powmod(h, exp, p)
        if g > 1:
            break
    return g


def generate_keys(g, p, q):
    x = randrange(2, q)  # x < q
    y = powmod(g, x, p)
    return x, y


def generate_params(L, N):
    p, q = generate_p_q(L, N)
    g = generate_g(p, q)
    return p, q, g


def sign(M, p, q, g, x):
    if not validate_params(p, q, g):
        raise Exception("Invalid params")
    while True:
        k = randrange(2, q)  # k < q
        r = powmod(g, k, p) % q
        m = int(sha1(M).hexdigest(), 16)
        try:
            s = (invert(k, q) * (m + x * r)) % q
            return r, s
        except ZeroDivisionError:
            pass


def verify(M, r, s, p, q, g, y):
    if not validate_params(p, q, g):
        raise Exception("Invalid params")
    if not validate_sign(r, s, q):
        return False
    try:
        w = invert(s, q)
    except ZeroDivisionError:
        return False
    m = int(sha1(M).hexdigest(), 16)
    u1 = (m * w) % q
    u2 = (r * w) % q
    # v = ((g ** u1 * y ** u2) % p) % q
    v = (powmod(g, u1, p) * powmod(y, u2, p)) % p % q
    if v == r:
        return True
    return False


def validate_params(p, q, g):
    if is_prime(p) and is_prime(q):
        return True
    if powmod(g, q, p) == 1 and g > 1 and (p - 1) % q:
        return True
    return False


def validate_sign(r, s, q):
    if r < 0 and r > q:
        return False
    if s < 0 and s > q:
        return False
    return True


if __name__ == "__main__":
    N = 160
    L = 1024
    p, q, g = generate_params(L, N)
    x, y = generate_keys(g, p, q)

    text = "CNS Rocks"
    M = str.encode(text, "ascii")
    r, s = sign(M, p, q, g, x)
    if verify(M, r, s, p, q, g, y):
        print('All ok')
    print(M, r, s, p, q, g, y, x, sep='\n')

'''
Output:
All ok
b'CNS Rocks'
77051681731201898973558653198015841760927444085
271009974619117165195008071611997114840669852363
169387655822814195910854919381507007620232969200658228944637167758811138785333285000483781061385341784658928035061746144870116918932010640020365540596964912871682824670003973941562398470089670358180424540261013253802664978591664538330466669240687693200957370121796506370988616177285821552987800427453785413541
748324291352731690693701886152678684464704738399
9177484460199906617676662407455248443027706317884753274056787834193867753963600227474115225073608794075933232407527022119971035261831537774346027230434389289050240492488848070611643231815839399763916515237854049968915091460750991134719777618038931055961312752768845755719578239783756959343389457269978811455
73751698188465483618879453816389779263335374823724048374846077986735001305036644506422170162368194181427341399111701229786368730088110041075787442647249194623264698519879111931390344484445391971059050855846373894205651136218124113465410359527290377895252392380881059086309588756415923443313476179203819097044
216445479034147461855943716525190896490236000268
'''