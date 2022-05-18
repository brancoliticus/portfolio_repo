#!BPY

from Blender import Scene , Mesh , Window , sys
import BPyMessages
import bpy

def build_points_list_from_file():
    plist=[]
    fname='/media/8AF411ABF4119B11/school/'
    fname+='sisteme_de_prelucrari_grafice/'
    fname+='graphic_engine/lab5in.pol'
    f=open(fname , 'r')
    
    for line in f:
        coords=line.rsplit(' ')
        plist.append([
            float( coords[0] ),
            float( coords[1] ),
            0.0])
    
    f.close()
    return plist
    

def build_points_list():
    return [[136.0 , 120.0 , 0.0],
            [164.0 , 143.0 , 0.0],
            [142.0 , 160.0 , 0.0],
            [112.0 , 133.0 , 0.0],
            [131.0 , 178.0 , 0.0],
            [167.0 , 165.0 , 0.0],
            [182.0 , 136.0 , 0.0]]

def add_points_to_mesh(mesh_data,points_to_add):
    for point in points_to_add:
        point[0] /= 100.0
        point[1]=(200.0 - point[1]) / 100.0
        
    edges_to_add=[]
    start=len(mesh_data.verts)
    end=len(points_to_add)
    for i in range(start,start+end):
        edges_to_add.append([i,i+1])
    edges_to_add[end-1][1]=start
        
    mesh_data.verts.extend(points_to_add)
    mesh_data.edges.extend(edges_to_add)
    
def main():
    
    current_scene=bpy.data.scenes.active
    active_object=current_scene.objects.active
    
    redo_active_mode=Window.EditMode()
    if redo_active_mode:
        Window.EditMode(0)
    Window.WaitCursor(1)
    
    mesh_data=active_object.getData(mesh=1)
    #points_to_add=build_points_list()
    points_to_add=build_points_list_from_file()
    add_points_to_mesh(mesh_data,points_to_add)
    
    if redo_active_mode:
        Window.EditMode(1)
    Window.WaitCursor(0)

if __name__ == '__main__':
    main()  