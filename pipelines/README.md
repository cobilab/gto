## Scripts / Pipelines

Some of the pipelines created using the GTO tools are available here. Inside of each directory, there is available the shell script and the README.md file details what tools where used and for what.


### Shell Script files

```bash
gto_complexity_profile_regions.sh
gto_complexity_profiles.sh
gto_create_viral_dataset.sh
gto_find_motif.sh
gto_map_rearrangements.sh
gto_map_rearrangements_proteins.sh
gto_metagenomics.sh
gto_proteins_complexity_profile_regions.sh
gto_simulate_rearragements.sh
gto_merge_fasta_dbs.sh
gto_build_xs_viral_db.sh
gto_create_sars_dataset.sh
```

### How to proceed when added a new script?
1. Create a directory here with the script name and inside created a README using the following template:

    # Script: gto_gto_script_name.sh

    Pipeline description...

    ```sh
    gto_script_name.sh
    ```

    The following block of code represents the essential information for this script:

    ```sh
    essential pieces of code
    ```

    ## Tools
    The GTO tools used and their role in this pipeline are the following:

    - **gto_tool_1**: the importance of this tool in the pipeline.
    - **gto_tool_2**: the importance of this tool in the pipeline.

2. Add the script name in this file and the README at the repository root.
3. The instruction for adding this in Conda will be added soon.
