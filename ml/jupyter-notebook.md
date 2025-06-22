```bash
# start jupyter lab in a python project

python -m venv venv
pip install -r requirements.txt
jupyter lab
```

### python virtual environment (venv)

```text

# python: Invokes the Python interpreter
# -m: Runs a Python module as a script
# venv: The built-in Python module for creating virtual environments
# venv: The name of the directory where the virtual environment will be created
python -m venv venv

above command will create following environment

venv/
├── bin/           # Activation scripts (Unix/macOS)
│   ├── activate
│   └── python
├── Scripts/       # Activation scripts (Windows)
│   ├── activate
│   └── python.exe
├── lib/           # Isolated Python libraries
└── pyvenv.cfg     # Configuration file
```

An isolated, self-contained directory that contains a specific python interpreter and a set of installed packages for a particular project

```bash
# Create a virtual environment
python3 -m venv myproject_env

# Activate the virtual environment
# On Unix/macOS:
source myproject_env/bin/activate
# On Windows:
myproject_env\Scripts\activate

# Install packages (only affects this environment)
pip install package_name

# Deactivate when done
deactivate
```

### jupyter notebook

```bash
# Install Jupyter
pip install jupyter

# Launch Jupyter Notebook
jupyter notebook
```

An open-source web application that allows you to create and share documents that contains live code, equations, visualizations, and
narrative text

widely used in data science, machine learning and scientific computing

- related tools
  - Google Colab: Cloud-based Jupyter notebook environment
  - VS Code: Supports Jupyter Notebook editing

# shortcuts

```bash
#-------------------------------------- command mode -----------------------------------------------
Enter         # Enter edit mode
a             # Insert a new cell above the current cell
b             # Insert a new cell below the current cell
dd            # Delete the current cell
z             # Undo cell deletion
y             # Change the cell type to code
m             # Change the cell type to Markdown
L             # Toggle line numbers.
j             # move to cell below
k             # move to cell above

#-------------------------------------- edit mode -----------------------------------------------
Esc           # Exit edit mode and enter command mode.
Shift + Enter #Execute the current cell and move the cursor to the next cell.
Tab           # Code completion or indent


#-------------------------------------both command & edit mode -----------------------------------
Ctrl + S      # Save the notebook.
```

- Get the full list of shortcuts by clicking on the "Help" menu in the Jupyter Notebook interface and selecting "Keyboard Shortcuts."
