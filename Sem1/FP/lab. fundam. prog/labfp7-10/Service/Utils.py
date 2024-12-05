def clear_file_content(filename):
    """
    Sterge continutul fisierului cu numele filename
    :param filename: numele fisierului din care vrem sa stergem continutul
    :type filename: str
    :return:
    :rtype:
    """
    with open(filename,'w') as f:
        pass