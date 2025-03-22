# **Parallel Quicksort using MPI**

## **Overview**
This project implements the **Parallel Quicksort Algorithm** using the **Message Passing Interface (MPI)** to enhance sorting performance across multiple processors. The project evaluates the efficiency, speedup, and execution time for different processor counts.

## **Features**
- Parallel implementation of **Quicksort** using MPI.
- Performance comparison with different processor counts (`-np 2, 4, 8, 16`).
- Handles large datasets (up to **10⁶ elements**).
- Performance analysis using execution time and speedup calculations.

## **Installation & Setup**
### **1️⃣ Install MPI**
If MPI is not installed, install it using:

#### **Ubuntu/Debian**
```sh
sudo apt update
sudo apt install -y mpich
```

#### **CentOS/RHEL**
```sh
sudo yum install -y mpich
```

#### **Mac (Homebrew Users)**
```sh
brew install mpich
```

### **2️⃣ Compile the Program**
```sh
mpicc parallel_quicksort.c -o parallel_quicksort
```

### **3️⃣ Run the Program**
Execute with different numbers of processors:
```sh
mpirun -np 4 ./parallel_quicksort
```

For large datasets:
```sh
mpirun -np 8 ./parallel_quicksort
```

## **Performance Analysis**
### **Execution Time Results**
| **Processes (`-np`)** | **Execution Time (`real`)** |
|----------------------|--------------------|
| **2**               | **0.279s**         |
| **4**               | **0.301s**         |
| **8**               | **0.301s**         |
| **16**              | **0.638s**         |

### **Observations**
- Best performance observed with **2 processors (`-np 2`)**.
- Increasing processors beyond **4** introduces **communication overhead**.
- Parallelization benefits depend on **dataset size**.

## **Future Enhancements**
✅ Test with **larger datasets (10⁷ elements)**.
✅ Compare with **other sorting algorithms (Merge Sort, Radix Sort)**.
✅ Implement **Hybrid MPI + OpenMP version**.


## **License**
This project is open-source and free to use under the MIT License.

