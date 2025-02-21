import os
import shutil

def move_backup_files():
    source_dir = os.getcwd()  
    backup_dir = os.path.join(source_dir, "backups")
    
    os.makedirs(backup_dir, exist_ok=True)
    
    for file in os.listdir(source_dir):
        if file.endswith(".FCBak"):
            source_path = os.path.join(source_dir, file)
            dest_path = os.path.join(backup_dir, file)
            
            # Move the file
            shutil.move(source_path, dest_path)
            print(f"Moved: {file} -> {backup_dir}")

if __name__ == "__main__":
    move_backup_files()
