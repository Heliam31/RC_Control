import os
from pathlib import Path
import re
try:
    from pathspec import PathSpec
    from pathspec.patterns import GitWildMatchPattern
except ImportError:
    print("Please install pathspec: pip install pathspec")
    raise

# Add folders to ignore here
IGNORED_FOLDERS = {
    '.git',
    '__pycache__',
    '.pytest_cache',
    '*.egg-info',
    'build',
    'dist',
    '.tox',
    '.venv',
    'venv',
    'node_modules',
    '.idea',
    '.vscode',
    "simpledroidble",
    "simplersble"

}

def find_missing_manifest_entries():
    # Read .gitignore patterns
    gitignore = Path('.gitignore')
    if gitignore.exists():
        with open(gitignore, 'r') as f:
            gitignore_content = f.read().splitlines()
        spec = PathSpec.from_lines(GitWildMatchPattern, gitignore_content)
    else:
        spec = PathSpec([])

    # Read current MANIFEST.in entries
    with open('MANIFEST.in', 'r') as f:
        manifest_content = f.read()

    # Get all included files from manifest
    included_files = set()
    for line in manifest_content.splitlines():
        if line.startswith('include '):
            included_files.add(line.split('include ')[1].strip())

    # Get all pruned/excluded paths
    excluded_paths = set()
    for line in manifest_content.splitlines():
        if line.startswith(('prune ', 'exclude ')):
            excluded_paths.add(line.split()[1].strip())

    # Find all files in project
    all_files = set()
    for root, dirs, files in os.walk('.'):
        # Skip ignored folders
        if any(ignored in root for ignored in IGNORED_FOLDERS):
            continue

        # Skip explicitly pruned directories
        if any(root.startswith(f'./{excluded}') for excluded in excluded_paths):
            continue

        for file in files:
            path = os.path.join(root, file)
            # Convert path to use forward slashes and remove leading ./
            path = path.replace('\\', '/').replace('./', '', 1)

            # Skip files that match gitignore patterns
            if spec.match_file(path):
                continue

            # Skip common file types that shouldn't be included
            if file.endswith(('.pyc', '.pyo', '.pyd')):
                continue

            all_files.add(path)

    # Find files that aren't in manifest
    missing_files = all_files - included_files

    # Print results
    if missing_files:
        print("Files found that aren't in MANIFEST.in:")
        for file in sorted(missing_files):
            print(f"include {file}")
    else:
        print("No missing files found!")

    return missing_files

def find_nonexistent_manifest_entries():
    # Read current MANIFEST.in entries
    with open('MANIFEST.in', 'r') as f:
        manifest_content = f.read()

    # Get all included files from manifest
    manifest_files = []
    for line in manifest_content.splitlines():
        if line.startswith('include '):
            manifest_files.append(line.split('include ')[1].strip())

    # Check each manifest entry
    nonexistent_files = []
    for file in manifest_files:
        if not os.path.exists(file):
            nonexistent_files.append(file)

    # Print results
    if nonexistent_files:
        print("\nFiles in MANIFEST.in that don't exist:")
        for file in sorted(nonexistent_files):
            print(f"Remove: include {file}")
    else:
        print("\nAll manifest entries exist!")

    return nonexistent_files

if __name__ == "__main__":
    missing = find_missing_manifest_entries()
    nonexistent = find_nonexistent_manifest_entries()
