from ctypes import cdll, c_bool, c_int32, c_int, \
    c_char, c_char_p, c_byte, c_float, c_double


def importDLL(dll_name):
    """
    Importation du fichier DLL C++
    """
    try:
        DLL_file_name = cdll.LoadLibrary(dll_name)
        useDLL = True
        print("La Bibliothèque à bien était chargé !")
    except IOError:
        print("La bibliothèque n'as pas été chargé avec succès ...")
