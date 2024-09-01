<h1>Compiler Design for Protocol Specification Language (PSL)</h1>

<h2>Project Overview</h2>
<p>
    This project focuses on designing and developing a compiler for a Protocol Specification Language (PSL). The compiler is divided into three main components:
</p>
<ol>
    <li><strong>Lexical Analyzer:</strong> Identifies components of the protocol specification, such as message types, fields, data structures, headers, and other relevant details.</li>
    <li><strong>Syntax and Semantic Analyzer:</strong> Improves the interpretation and processing of communication protocols by analyzing their semantic meaning and generating intermediate representation code.</li>
    <li><strong>Intermediate Code Generator and Code Optimization:</strong> Enhances the efficiency and performance of protocol-related operations by optimizing protocol specifications and generating machine-readable object code.</li>
</ol>

<h2>Project Structure</h2>
<p>
    The repository is organized into three folders, each serving a distinct function in the compilation process:
</p>
<ul>
    <li><strong>Folder 1:</strong> Contains the lexical analyzer for PSL. This folder includes code to parse protocol specifications and identify various components.</li>
    <li><strong>Folder 2:</strong> Contains the syntax and semantic analyzer for PSL. This folder includes code to analyze the semantic meaning of protocol specifications and generate intermediate representation code.</li>
    <li><strong>Folder 3:</strong> Contains the intermediate code generator and code optimization tools for PSL. This folder includes code to optimize protocol specifications and generate machine-readable object code.</li>
</ul>

<p>
    Each folder includes an input file that serves as the input for the respective component. The input for each component is the output of the previous folder's process.
</p>

<h2>Clone the Repository</h2>
<p>
    To clone the repository, use the following command:
</p>
<pre><code>git clone https://github.com/Imaadhajwane/Compiler_Design_Project.git</code></pre>

<h2>Run the Files</h2>
<p>
    After cloning the repository, navigate to the respective folders to run the files. Here are the steps for each folder:
</p>
<ol>
    <li><strong>Folder 1:</strong> Navigate to this folder and run the "try.c".</li>
    <li><strong>Folder 2:</strong> Navigate to this folder and run the "experiemnt.c". The input file for this step is the output from Folder 1.</li>
    <li><strong>Folder 3:</strong> Navigate to this folder and run the "experiemnt3.c". The input file for this step is the output from Folder 2.</li>
</ol>
