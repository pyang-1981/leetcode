
i = -123
s = str(i)
if s.startswith('-'):
    inverse = s[1][:0:-1]
    inverse = '-' + inverse
else:
    inverse = s[::-1]

print(inverse)
