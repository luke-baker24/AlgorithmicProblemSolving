# runner.py

## CITE: Made runner using Gemini. 


import subprocess
import os
import sys
import shutil
import glob # For finding test case files

# --- Configuration ---
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
SUBMISSIONS_DIR = os.path.join(BASE_DIR, "submissions", "accepted")
SAMPLE_TEST_CASES_DIR = os.path.join(BASE_DIR, "sample")
SECRET_TEST_CASES_DIR = os.path.join(BASE_DIR, "secret")
COMPILED_DIR = os.path.join(BASE_DIR, "compiled") # Directory for compiled outputs

# Solution file mapping
SOLUTION_CONFIG = {
    0: {"file_name": "judge_solution.java", "language": "java", "class_name": "judge_solution"},
    1: {"file_name": "java_solution.java", "language": "java", "class_name": "java_solution"},
    2: {"file_name": "python_solution.py", "language": "python"},
    3: {"file_name": "c_plus_plus_solution.cpp", "language": "cpp", "executable_name": "cpp_solution_exec"}, # .exe will be added on Windows by g++
}

# Timeout for running submissions (in seconds)
RUN_TIMEOUT = 5

# --- Helper Functions ---

def check_executables():
    """Checks if necessary compilers and interpreters are available."""
    required = {
        #"java": ["javac", "java"],
        #"python": [sys.executable],
        "cpp": ["g++"]
    }
    missing = []
    for lang_reqs in required.values():
        for exe in lang_reqs:
            if shutil.which(exe) is None:
                missing.append(exe)
    if missing:
        print(f"Error: The following required executables were not found in your PATH: {', '.join(missing)}")
        print("Please install them or ensure they are in your system's PATH.")
        sys.exit(1)
    print("All required executables (javac, java, python, g++) found.")

def compile_java(java_file_path, class_output_dir):
    """Compiles a Java file into the specified output directory. Returns True on success, False otherwise."""
    print(f"Compiling {os.path.basename(java_file_path)} into {class_output_dir}...")
    # The -d option tells javac where to place generated class files.
    compile_command = [shutil.which("javac"), "-d", class_output_dir, java_file_path]
    try:
        process = subprocess.run(compile_command, capture_output=True, text=True, check=False, timeout=RUN_TIMEOUT + 10)
        if process.returncode != 0:
            print(f"Java compilation failed for {os.path.basename(java_file_path)}.")
            print("Error output:")
            print(process.stderr)
            return False
        print("Java compilation successful.")
        return True
    except subprocess.TimeoutExpired:
        print(f"Java compilation timed out for {os.path.basename(java_file_path)}.")
        return False
    except Exception as e:
        print(f"An error occurred during Java compilation: {e}")
        return False

def run_java(class_name, classpath_dir, input_data):
    """Runs a compiled Java class using the specified classpath. Returns (stdout, stderr, return_code)."""
    # The -cp (classpath) option tells java where to find .class files.
    run_command = [shutil.which("java"), "-cp", classpath_dir, class_name]
    try:
        process = subprocess.run(run_command, input=input_data, capture_output=True, text=True, check=False, timeout=RUN_TIMEOUT)
        return process.stdout, process.stderr, process.returncode
    except subprocess.TimeoutExpired:
        return None, f"Execution timed out after {RUN_TIMEOUT} seconds.", -1 
    except Exception as e:
        return None, str(e), -1

def compile_cpp(cpp_file_path, output_executable_path):
    """Compiles a C++ file to the specified executable path. Returns True on success, False otherwise."""
    print(f"Compiling {os.path.basename(cpp_file_path)} to {output_executable_path}...")
    # The -o option tells g++ where to place the output executable.
    compile_command = [shutil.which("g++"), cpp_file_path, "-o", output_executable_path, "-std=c++11"]
    try:
        process = subprocess.run(compile_command, capture_output=True, text=True, check=False, timeout=RUN_TIMEOUT + 10)
        if process.returncode != 0:
            print(f"C++ compilation failed for {os.path.basename(cpp_file_path)}.")
            print("Error output:")
            print(process.stderr)
            return False
        print(f"C++ compilation successful. Executable: {os.path.basename(output_executable_path)}")
        return True
    except subprocess.TimeoutExpired:
        print(f"C++ compilation timed out for {os.path.basename(cpp_file_path)}.")
        return False
    except Exception as e:
        print(f"An error occurred during C++ compilation: {e}")
        return False

def run_cpp(executable_path, input_data):
    """Runs a compiled C++ executable. Returns (stdout, stderr, return_code)."""
    run_command = [executable_path]
    try:
        process = subprocess.run(run_command, input=input_data, capture_output=True, text=True, check=False, timeout=RUN_TIMEOUT)
        return process.stdout, process.stderr, process.returncode
    except subprocess.TimeoutExpired:
        return None, f"Execution timed out after {RUN_TIMEOUT} seconds.", -1
    except Exception as e:
        return None, str(e), -1

def run_python(python_file_path, input_data):
    """Runs a Python script. Returns (stdout, stderr, return_code)."""
    run_command = [sys.executable, python_file_path]
    try:
        process = subprocess.run(run_command, input=input_data, capture_output=True, text=True, check=False, timeout=RUN_TIMEOUT)
        return process.stdout, process.stderr, process.returncode
    except subprocess.TimeoutExpired:
        return None, f"Execution timed out after {RUN_TIMEOUT} seconds.", -1
    except Exception as e:
        return None, str(e), -1

def find_test_case_bases(test_dir):
    """Finds .in files in a directory and returns a sorted list of base names (e.g., 'test1' from 'test1.in')."""
    if not os.path.isdir(test_dir):
        return []
    in_files = glob.glob(os.path.join(test_dir, "*.in"))
    test_case_bases = sorted([os.path.splitext(os.path.basename(f))[0] for f in in_files])
    return test_case_bases

def compare_outputs(actual_output, expected_output_content):
    """Compares actual output with expected output, normalizing whitespace."""
    actual_output_str = actual_output if actual_output is not None else ""
    expected_output_str = expected_output_content if expected_output_content is not None else ""

    actual_lines = [line.rstrip() for line in actual_output_str.strip().replace('\r\n', '\n').split('\n')]
    expected_lines = [line.rstrip() for line in expected_output_str.strip().replace('\r\n', '\n').split('\n')]

    if actual_lines == [''] and not any(l.strip() for l in expected_lines): actual_lines = []
    if expected_lines == [''] and not any(l.strip() for l in actual_lines): expected_lines = []
    
    if not actual_lines and not expected_lines:
        return True

    return actual_lines == expected_lines

# --- Main Execution Logic ---
def main():
    check_executables()

    # Create the compiled directory; if it exists, it's fine.
    os.makedirs(COMPILED_DIR, exist_ok=True)
    print(f"Using directory for compiled files: {COMPILED_DIR}")

    print("\nMirroredLazerMaze Solution Tester")
    print("---------------------------------")
    print("Available solutions:")
    for key, val in SOLUTION_CONFIG.items():
        print(f"  {key}: {val['file_name']} ({val['language']})")

    choice = -1
    while choice not in SOLUTION_CONFIG:
        try:
            choice_str = input(f"Enter your choice (0-{len(SOLUTION_CONFIG)-1}): ")
            choice = int(choice_str)
            if choice not in SOLUTION_CONFIG:
                print("Invalid choice. Please try again.")
        except ValueError:
            print("Invalid input. Please enter a number.")

    selected_solution = SOLUTION_CONFIG[choice]
    file_name = selected_solution["file_name"]
    language = selected_solution["language"]
    solution_file_path = os.path.join(SUBMISSIONS_DIR, file_name)

    if not os.path.exists(solution_file_path):
        print(f"\nError: Solution file not found: {solution_file_path}")
        # Clean up COMPILED_DIR before exiting if it was created
        if os.path.exists(COMPILED_DIR):
            try:
                shutil.rmtree(COMPILED_DIR)
            except OSError as e:
                print(f"Warning: Could not remove compiled directory {COMPILED_DIR} on error: {e}")
        return

    print(f"\nSelected to test: {file_name} ({language})")

    compiled_successfully = True
    # Path for the C++ executable or Java class name
    target_executable_path = None # For C++
    java_class_name = None      # For Java

    if language == "java":
        java_class_name = selected_solution["class_name"]
        # Java .class files will be placed in COMPILED_DIR by javac's -d option.
        if not compile_java(solution_file_path, COMPILED_DIR):
            compiled_successfully = False
    elif language == "cpp":
        # Construct the full path for the output executable inside COMPILED_DIR
        # g++ typically adds .exe on Windows automatically if not specified.
        # For consistency, we can define it or let g++ handle it.
        # If executable_name is "cpp_solution_exec", on Windows it becomes "cpp_solution_exec.exe"
        base_exec_name = selected_solution["executable_name"]
        if sys.platform == "win32" and not base_exec_name.endswith(".exe"):
             # It's common for g++ on Windows to add .exe if not present in -o argument.
             # To be explicit for run_cpp, we can form the path with .exe
             # or ensure compile_cpp output_executable_path is what we expect.
             # For simplicity, let's assume g++ output name matches `base_exec_name` or `base_exec_name.exe`
             # and `run_cpp` will just use this path.
             target_executable_path = os.path.join(COMPILED_DIR, base_exec_name + ".exe")
        else:
            target_executable_path = os.path.join(COMPILED_DIR, base_exec_name)

        # Pass the full desired output path to compile_cpp
        if not compile_cpp(solution_file_path, target_executable_path):
            compiled_successfully = False


    if not compiled_successfully:
        print("Cannot proceed with testing due to compilation failure.")
        if os.path.exists(COMPILED_DIR): # Attempt cleanup even on compilation fail
            try:
                shutil.rmtree(COMPILED_DIR)
                print(f"Cleaned up compiled directory: {COMPILED_DIR}")
            except OSError as e:
                print(f"Warning: Could not remove compiled directory {COMPILED_DIR} after failed compilation: {e}")
        return

    # --- Test Case Execution ---
    test_case_details = [] 
    for test_dir_label, test_dir_actual_path in [("sample", SAMPLE_TEST_CASES_DIR), ("secret", SECRET_TEST_CASES_DIR)]:
        if os.path.isdir(test_dir_actual_path):
            base_names = find_test_case_bases(test_dir_actual_path)
            for base in base_names:
                in_file_path = os.path.join(test_dir_actual_path, base + ".in")
                ans_file_path = os.path.join(test_dir_actual_path, base + ".ans")
                
                if os.path.exists(ans_file_path): 
                    test_case_details.append({
                        "name": f"{test_dir_label}/{base}",
                        "in_file": in_file_path,
                        "ans_file": ans_file_path 
                    })
                else:
                    print(f"Warning: Missing corresponding .ans file for {in_file_path}, skipping test case '{base}' in '{test_dir_label}'.")
        else:
            print(f"Info: Test case directory not found: {test_dir_actual_path}")

    if not test_case_details:
        print("\nNo valid test cases (with .in and .ans pairs) found. Nothing to test.")
        # Fall through to cleanup
    else:
        print(f"\nFound {len(test_case_details)} test case(s). Running tests...\n")
        passed_count = 0
        total_count = len(test_case_details)

        for i, test_case in enumerate(test_case_details):
            print(f"--- Test Case {i+1}/{total_count}: {test_case['name']} ---")
            input_data_content = ""
            expected_ans_content = ""

            try:
                with open(test_case["in_file"], "r", encoding="utf-8") as f_in:
                    input_data_content = f_in.read()
                with open(test_case["ans_file"], "r", encoding="utf-8") as f_ans: 
                    expected_ans_content = f_ans.read()
            except FileNotFoundError as e:
                print(f"Error reading test case file: {e}. Skipping this test case.")
                result_status = "ERROR (File Missing)"
                status_color_start = "\033[91m" 
                status_color_end = "\033[0m"    
                print(f"Result: {status_color_start}{result_status}{status_color_end}")
                continue 
            except Exception as e:
                print(f"An unexpected error occurred while reading test files for {test_case['name']}: {e}")
                result_status = "ERROR (File Read)"
                status_color_start = "\033[91m" 
                status_color_end = "\033[0m"    
                print(f"Result: {status_color_start}{result_status}{status_color_end}")
                continue

            stdout_val, stderr_val, return_code_val = None, None, -1

            if language == "java":
                # For Java, COMPILED_DIR is the classpath.
                stdout_val, stderr_val, return_code_val = run_java(java_class_name, COMPILED_DIR, input_data_content)
            elif language == "python":
                stdout_val, stderr_val, return_code_val = run_python(solution_file_path, input_data_content)
            elif language == "cpp":
                # Ensure target_executable_path exists before trying to run it, especially for Windows .exe
                actual_executable_to_run = target_executable_path
                if sys.platform == "win32" and not os.path.exists(actual_executable_to_run) and os.path.exists(os.path.splitext(actual_executable_to_run)[0]):
                    # If "program.exe" doesn't exist but "program" does, g++ might not have added .exe
                    # This case is less likely if -o explicitly names .exe, but good to be cautious.
                    # However, our compile_cpp explicitly passes target_executable_path (which includes .exe on Windows)
                    pass # Assuming compile_cpp created the correct file.

                if not os.path.exists(actual_executable_to_run):
                     print(f"Error: Compiled C++ executable not found at {actual_executable_to_run}")
                     result_status = "ERROR (Executable Missing)"
                     status_color_start = "\033[91m"
                     status_color_end = "\033[0m"
                     print(f"Result: {status_color_start}{result_status}{status_color_end}\n")
                     continue # Skip this test case

                stdout_val, stderr_val, return_code_val = run_cpp(actual_executable_to_run, input_data_content)


            result_status = "FAILED"
            status_color_start = "\033[91m" 
            status_color_end = "\033[0m"    

            is_timeout = "execution timed out" in (stderr_val or "").lower()
            
            if return_code_val == 0 and not is_timeout:
                if compare_outputs(stdout_val, expected_ans_content):
                    result_status = "PASSED"
                    status_color_start = "\033[92m" 
                    passed_count += 1
                else:
                    result_status = "FAILED (Wrong Answer)"
            elif is_timeout:
                result_status = "FAILED (Timeout)"
            elif return_code_val != 0 :
                result_status = f"FAILED (Runtime Error - Code: {return_code_val})"
                if stderr_val: print(f"Stderr:\n{stderr_val.strip()}")
            
            print(f"Result: {status_color_start}{result_status}{status_color_end}\n")

        print("--- Testing Complete ---")
        print(f"Total Test Cases: {total_count}")
        print(f"Passed: {passed_count}")
        print(f"Failed: {total_count - passed_count}")

        overall_message_text = ""
        if total_count == 0: # Should be caught by "No valid test cases" earlier, but as a safeguard
            final_status_color = "\033[93m" 
            overall_message_text = f"Overall Result: {passed_count}/{total_count} - NO TESTS RUN"
        elif passed_count == total_count:
            final_status_color = "\033[92m" 
            overall_message_text = f"Overall Result: {passed_count}/{total_count} - ALL PASSED"
        else: 
            final_status_color = "\033[91m" 
            overall_message_text = f"Overall Result: {passed_count}/{total_count} - SOME FAILED"
        
        print(f"{final_status_color}{overall_message_text}{status_color_end}")

    # --- Final Cleanup of Compiled Directory ---
    if os.path.exists(COMPILED_DIR):
        try:
            shutil.rmtree(COMPILED_DIR)
            print(f"Successfully cleaned up compiled directory: {COMPILED_DIR}")
        except OSError as e:
            print(f"Warning: Could not remove compiled directory {COMPILED_DIR}: {e}")

if __name__ == "__main__":
    main()
