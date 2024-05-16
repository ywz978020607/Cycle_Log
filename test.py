import ctypes

so = ctypes.CDLL("./Cycle_Log.so")

so.FileInit(b'tmp.log', b'out.log', 200*4-2)

for idx in range(500):
    so.FileWriteLog(str(idx).zfill(3).encode()+b'\n')
so.FileWriteLog(str('a').encode()+b'\n')
so.FileClose()



