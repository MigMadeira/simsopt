import numpy as np
from scipy.spatial.transform import Rotation as R

try:
    from pyevtk.hl import gridToVTK
except ImportError:
    gridToVTK = None

import simsoptpp as sopp
from .._core.dev import SimsoptRequires

__all__ = ['cylinder_to_vtk']


@SimsoptRequires(gridToVTK is not None, "to_vtk method requires pyevtk module")
def cylinder_to_vtk(cylinder: sopp.Cylinder, filename, n_theta=100, n_z=100, extra_data=None):
    """
    Export the surface to a VTK format file, which can be read with
    Paraview. This function requires the ``pyevtk`` python
    package, which can be installed using ``pip install pyevtk``.
    Args:
        filename: Name of the file to write
        extra_data: An optional data field on the surface, which can be associated with a colormap in Paraview.
    """   
    ax_vec = np.array(cylinder.axis_vector)

    x = []
    y = []
    z = []

    def perpendicular_vector(v):
        if (v[1] <= 1e-10 and v[2] <= 1e-10):
            if v[0] == 0:
                raise ValueError('zero vector')
            else:
                return np.cross(v, [0, 1, 0])
        return np.cross(v, [1, 0, 0])

    perp_vec = perpendicular_vector(ax_vec)
    d_theta = np.linspace(0, 1, n_theta)
    d_z = np.linspace(0, 1, n_z)

    for i in range(n_z):
        vec1 = cylinder.height * d_z[i] * ax_vec

        for j in range(n_theta):
            rotation = R.from_rotvec(2 * np.pi * d_theta[j] * ax_vec) 

            vec2 = rotation.apply(perp_vec)
            vec2 = vec2/(vec2[0]**2 + vec2[1]**2 + vec2[2]**2)**0.5

            x.append(cylinder.base_point[0] + vec1[0] + cylinder.radius * vec2[0])
            y.append(cylinder.base_point[1] + vec1[1] + cylinder.radius * vec2[1])
            z.append(cylinder.base_point[2] + vec1[2] + cylinder.radius * vec2[2])

    x = np.array(x).reshape((1, n_z, n_theta))
    y = np.array(y).reshape((1, n_z, n_theta))
    z = np.array(z).reshape((1, n_z, n_theta))

    gridToVTK(str(filename), x, y, z, pointData=extra_data)
