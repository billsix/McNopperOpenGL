/*
 * GLUS - Modern OpenGL, OpenGL ES and OpenVG Utilities. Copyright (C) since
 * 2010 Norbert Nopper
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GLUS_SPHERE_H_
#define GLUS_SPHERE_H_

/**
 * Copies a sphere.
 *
 * @param resultCenter Destination center.
 * @param resultRadius Destination radius.
 * @param center	   Source center.
 * @param radius	   Source radius.
 */
GLUSAPI GLUSvoid GLUSAPIENTRY glusSphereCopyf(GLUSfloat resultCenter[4],
                                              GLUSfloat resultRadius,
                                              const GLUSfloat center[4],
                                              const GLUSfloat radius);

/**
 * Calculates the signed distance from a sphere to a point. If the value is
 * negative, the point is inside the sphere.
 *
 * @param center The center of the sphere.
 * @param radius The radius of the sphere.
 * @param point	 The used point.
 *
 * @return The signed distance.
 */
GLUSAPI GLUSfloat GLUSAPIENTRY
glusSphereDistancePoint4f(const GLUSfloat center[4], const GLUSfloat radius,
                          const GLUSfloat point[4]);

#endif /* GLUS_SPHERE_H_ */
