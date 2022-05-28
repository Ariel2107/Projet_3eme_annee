from ctypes import cdll


def importDLL(dll_name):
    """
    Importation du fichier DLL C++
    """
    try:
        DLL_file_name = cdll.LoadLibrary(dll_name)
        useDLL = True
        print("La Bibliothèque à bien était chargé !")
    except IOError:
        print("La bibliothèque n'as pas été chargé avec succès !")