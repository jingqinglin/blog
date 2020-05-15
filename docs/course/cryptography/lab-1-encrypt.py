import sys
import codecs

MSGS = ["LinJingqing", "Code"]


def split_hex(h, dtype='int'):
    '''
    :param h: A hex string. Example: "315c4eea". Its length should be an even number.
    :return: A list of integer corresponding to every two letters in h
    '''
    if dtype == 'int':
        split = [int(h[2 * i:2 * i + 2], 16) for i in range(len(h) // 2)]
    elif dtype == 'str' or 'string':
        split = [h[2 * i:2 * i + 2] for i in range(len(h) // 2)]
    else:
        split = [int(h[2 * i:2 * i + 2], 16) for i in range(len(h) // 2)]

    return split


def strxor(a, b):
    # xor two strings of different lengths
    if len(a) > len(b):
        return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a[:len(b)], b)])
    else:
        return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a, b[:len(a)])])


def random(size=16):
    return open("plaintext.txt").read(size)


def encrypt(key, msg):
    c = strxor(key, msg)
    c = codecs.encode(bytes(c, encoding='utf-8'), 'hex')
    return c


def decrypt(key, cipher):
    cipher = ''.join([chr(x) for x in split_hex(cipher)])
    msg = strxor(key, cipher)
    return msg


def main():
    key = random(1024)
    ciphertexts = [encrypt(key, msg) for msg in MSGS]
    print(ciphertexts)
    plaintexts = [decrypt(key, cipher) for cipher in ciphertexts]
    print(plaintexts)


if __name__ == "__main__":
    main()
