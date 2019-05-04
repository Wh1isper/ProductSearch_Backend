import os
import random


class Generater():
    def __init__(self, path="./Cache", StoreNum=100, ComNum=100, LabelNum=10, drop=0.5):
        self.DROP = drop
        self.PATH = path
        self.STORENUM = StoreNum
        self.COMNUM = ComNum
        self.LABELNUM = LabelNum
        self.StoreName = ["StoreName" + repr(x) for x in range(1, self.STORENUM + 1)]
        self.Plat = ["Plat_1", "Plat_2", "Plat_3"]
        self.Com = [self.creatCom(self.COMNUM) for x in range(self.STORENUM)]
        self.Label = [self.creatLabel(self.LABELNUM) for x in range(self.LABELNUM)]

    def creatCom(self, ComNum):
        Store = []
        for i in range(ComNum):
            if random.random() < self.DROP:
                continue
            Com = []
            Com.append("Com" + repr(i))
            Com.append(repr(i * 0.98))
            Store.append(Com)
        return Store

    def creatLabel(self, LabelNum):
        Store = []
        for i in range(LabelNum):
            if random.random() < self.DROP:
                continue
            Store.append("Label" + repr(i))
        return Store

    def run(self):
        if not os.path.exists(self.PATH):
            os.makedirs(self.PATH)
        print(self.StoreName)
        print(self.Com)
        print(self.Label)
        for i in range(len(self.StoreName)):
            with open(os.path.join(self.PATH, repr(i + 1) + ".pds"), "w") as f:
                f.write(self.StoreName[i] + '\n')
                f.write(self.Plat[i % 3] + '\n')
                f.write(repr(i + 1) + '\n')
                for j in range(len(self.Com[i])):
                    f.write(self.Com[i][j][0] + '\n')
                    f.write(self.Com[i][j][1] + '\n')
                    f.write(repr(i + 1) + '\n')
                    f.write(repr(j + 1) + '\n')
                    label = self.Label[random.randint(0, 9)]
                    f.write(repr(len(label)) + '\n')
                    for L in label:
                        f.write(L + '\n')
        with open(os.path.join(self.PATH, "StoreList.txt"), "w") as f:
            for i in range(len(self.StoreName)):
                f.write(repr(i + 1) + '\n')


if __name__ == '__main__':
    session = Generater()
    session.run()
