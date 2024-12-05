import shutil

def copy_file_content(dest,source):
    shutil.copyfile(source,dest)
def clear_file_content(name):
    with open(name,'w') as f:
        pass