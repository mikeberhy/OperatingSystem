import os
import shutil

class SimpleOneOS:
    def __init__(self):
        print("Welcome to SimpleOneOS! Type 'help' to see available commands.")

    def create_file(self, filename):
        with open(filename, 'w') as f:
            pass
        print(f"File '{filename}' created successfully.")

    def create_directory(self, dirname):
        os.makedirs(dirname, exist_ok=True)
        print(f"Directory '{dirname}' created successfully.")

    def list_contents(self, path='.'):
        contents = os.listdir(path)
        for item in contents:
            print(item)

    def delete_file(self, filename):
        try:
            os.remove(filename)
            print(f"File '{filename}' deleted successfully.")
        except FileNotFoundError:
            print(f"File '{filename}' not found.")

    def delete_directory(self, dirname):
        try:
            shutil.rmtree(dirname)
            print(f"Directory '{dirname}' deleted successfully.")
        except FileNotFoundError:
            print(f"Directory '{dirname}' not found.")

    def rename(self, old_name, new_name):
        try:
            os.rename(old_name, new_name)
            print(f"'{old_name}' renamed to '{new_name}'.")
        except FileNotFoundError:
            print(f"'{old_name}' not found.")

    def run(self):
        while True:
            command = input("SimpleOneOS> ").strip().split()
            if len(command) == 0:
                continue
            if command[0].lower() == 'exit':
                print("Exiting SimpleOneOS. Goodbye!")
                break
            elif command[0].lower() == 'help':
                self.show_help()
            elif command[0].lower() == 'createfile':
                if len(command) > 1:
                    self.create_file(command[1])
                else:
                    print("Usage: createfile <filename>")
            elif command[0].lower() == 'createdir':
                if len(command) > 1:
                    self.create_directory(command[1])
                else:
                    print("Usage: createdir <dirname>")
            elif command[0].lower() == 'list':
                if len(command) > 1:
                    self.list_contents(command[1])
                else:
                    self.list_contents()
            elif command[0].lower() == 'deletefile':
                if len(command) > 1:
                    self.delete_file(command[1])
                else:
                    print("Usage: deletefile <filename>")
            elif command[0].lower() == 'deletedir':
                if len(command) > 1:
                    self.delete_directory(command[1])
                else:
                    print("Usage: deletedir <dirname>")
            elif command[0].lower() == 'rename':
                if len(command) > 2:
                    self.rename(command[1], command[2])
                else:
                    print("Usage: rename <oldname> <newname>")
            else:
                print(f"Unknown command: {command[0]}")

    def show_help(self):
        print("""
        Available commands:
        createfile <filename>   - Create a new empty file
        createdir <dirname>     - Create a new directory
        list [path]             - List files and directories
        deletefile <filename>   - Delete a file
        deletedir <dirname>     - Delete a directory and its contents
        rename <oldname> <newname> - Rename a file or directory
        exit                    - Exit the OS
        """)

if __name__ == '__main__':
    os_shell = SimpleOneOS()
    os_shell.run()
