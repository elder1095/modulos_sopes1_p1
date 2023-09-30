// Info de los modulos
#include <linux/module.h>
// Info del kernel en tiempo real
#include <linux/kernel.h>
#include <linux/sched.h>

// Headers para modulos
#include <linux/init.h>
// Header necesario para proc_fs
#include <linux/proc_fs.h>
// Para dar acceso al usuario
#include <asm/uaccess.h>
// Para manejar el directorio /proc
#include <linux/seq_file.h>
// Para get_mm_rss
#include <linux/mm.h>
const long minute = 60;
const long hours = minute * 60;
const long day = hours * 24;
const long megabyte = 1024 * 1024;

struct sysinfo si;

static void init_meminfo(void){
    si_meminfo(&si);            
};

struct task_struct *cpu; // Estructura que almacena info del cpu

// Almacena los procesos
struct list_head *lstProcess;
// Estructura que almacena info de los procesos hijos
struct task_struct *child;
unsigned long rss;
unsigned long total_ram, ram_en_uso, ram_libre;
unsigned long porcentaje_en_uso;
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulo de RAM tarea No. 4 Sopes 1");
MODULE_AUTHOR("ELDER OBDULIO CALDERON NAVARIJO");

static int escribir_archivo(struct seq_file *archivo, void *v) {
    init_meminfo();
    total_ram = (si.totalram * si.mem_unit) / megabyte;
    ram_en_uso = (si.totalram - si.freeram) * si.mem_unit / megabyte;
    ram_libre = si.freeram * si.mem_unit / megabyte;
    porcentaje_en_uso = (ram_en_uso * 100 / total_ram);


    seq_printf(archivo, "Total_Ram: %lu\n", total_ram);
    seq_printf(archivo, "Ram_en_Uso: %lu\n", ram_en_uso);
    seq_printf(archivo, "Ram_Libre: %lu\n", ram_libre);
    //double porcent = (double)ram_en_uso / total_ram * 100);
    seq_printf(archivo, "Ram_en_Uso: %lu\n", porcentaje_en_uso);
    


    // seq_printf(archivo, "mem_unit: ");
    // seq_printf(archivo, "%u", si.mem_unit);
    // seq_printf(archivo, ",\n");
    // seq_printf(archivo, "Total_Ram: ");
    // seq_printf(archivo, "%lu", si.totalram/si.mem_unit);
    // seq_printf(archivo, ",\n");
    // seq_printf(archivo, "Ram_en_Uso: ");
    // seq_printf(archivo, "%lu", (si.totalram - si.freeram)/si.mem_unit);
    // seq_printf(archivo, ",\n");
    // seq_printf(archivo, "Ram_Libre: ");
    // seq_printf(archivo, "%lu", si.freeram/si.mem_unit);
    // seq_printf(archivo, ",\n");
    //seq_printf(archivo, "Porcentaje_en_uso: ");
    //seq_printf(archivo, "%.2f%%", ((double)used_ram / si.totalram) * 100.0);
    //seq_printf(archivo, ",\n");
    return 0;
};

//Funcion que se ejecutara cada vez que se lea el archivo con el comando CAT
static int al_abrir(struct inode *inode, struct file *file)
{
    return single_open(file, escribir_archivo, NULL);
};

//Si el kernel es 5.6 o mayor se usa la estructura proc_ops
static struct proc_ops operaciones =
{
    .proc_open = al_abrir,
    .proc_read = seq_read
};

//Funcion a ejecuta al insertar el modulo en el kernel con insmod
static int _insert(void)
{
    proc_create("ram_201701095", 0, NULL, &operaciones);
    printk(KERN_INFO "Elder Obdulio Calderon Navarijo\n");
    return 0;
}

//Funcion a ejecuta al remover el modulo del kernel con rmmod
static void _remove(void)
{
    remove_proc_entry("ram_201701095", NULL);
    printk(KERN_INFO "Segundo Semestre 2023\n");
}

module_init(_insert);
module_exit(_remove);
