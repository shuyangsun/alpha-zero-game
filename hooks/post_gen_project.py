import shutil

if "{{ cookiecutter.github_actions }}" != "y":
    shutil.rmtree(".github")
