from os import path, listdir

class DialogUtils:
    
    @classmethod
    def getDialog(cls, id, type,level):
        lista = []
        with open(path.join("dialogit", cls.getDialogPath(id, type,level)), "r") as f:
            lista.extend(line for line in f if "#" not in line)
        return lista

    @classmethod
    def getDialogPath(cls, id, type,level):
        tyyppi = "Fish" if type == 403 else "Sign"
        fname = f"L{str(level)}{tyyppi}{str(id)}"
        for file in listdir(path.join('Dialogit')):
            if fname in file:
                return file