[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 100
  ny = 100
  xmax = 0.304
  ymax = 0.0257
[]

[Variables]
  [pressure]
    # Adds lagrange variable by default so left blank
  []
[]

[Kernels]
  [darcy_pressure]
    type = DarcyPressure
    variable = pressure
  []
[]

[BCs]
  [inlet]
    type = ADDirichletBC
    variable = pressure
    boundary = left
    value = 4000 # Pa
  []
  [outlet]
    type = ADDirichletBC
    variable = pressure
    boundary = right
    value = 0
  []
[]

[Materials]
  [spheres]
    type = ADGenericConstantMaterial
    prop_names = " permeability viscosity "
    prop_values = " 0.8451e-9 7.98e-4 "
  []
[]

[Problem]
  type = FEProblem
  coord_type = RZ   #Axisemetric in RZ? whats that mean
  rz_coord_axis = X #SO it can be modeled as a flat plane through the middle of the pipe? because it should be the same as you spin around the pipe
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
[]
