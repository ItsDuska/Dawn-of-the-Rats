from os import path, listdir

class DialogUtils:

    @classmethod
    def getDialog(cls, id, type,level):
        #Return the dialog in a list
        lista = []
        with open(path.join("dialogit", cls.getDialogPath(id, type,level)), "r") as f:
            lista.extend(line for line in f if "#" not in line)
        return lista

    @classmethod
    def getDialogPath(cls, id, type,level):
        #Get the path to the dialog file
        #Object type is the object that shows the dialog. (signs or npcs)
        objectType = "Fish" if type == 403 else "Sign" # fish is an NPC
        fileName = f"L{str(level)}{objectType}{str(id)}"
        for file in listdir(path.join('Dialogit')):
            if fileName in file:
                return file

