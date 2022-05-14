/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2020 SIGNET Lab, Department of Information Engineering,
 * University of Padova
 * Copyright (c) 2020 Institute for the Wireless Internet of Things,
 * Northeastern University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MATRIX_BASED_CHANNEL_H
#define MATRIX_BASED_CHANNEL_H

#include <complex.h>
#include <ns3/object.h>
#include <ns3/nstime.h>
#include <ns3/vector.h>
#include <ns3/phased-array-model.h>
#include <tuple>

namespace ns3 {

class MobilityModel;

/**
 * \ingroup spectrum
 *
 * This is an interface for a channel model that can be described
 * by a channel matrix, e.g., the 3GPP Spatial Channel Models,
 * which is generally used in combination with antenna arrays
 */
class MatrixBasedChannelModel : public Object
{
public:
  /**
   * Destructor for MatrixBasedChannelModel
   */
  virtual ~MatrixBasedChannelModel ();

  typedef std::vector<double> DoubleVector; //!< type definition for vectors of doubles
  typedef std::vector<DoubleVector> Double2DVector; //!< type definition for matrices of doubles
  typedef std::vector<Double2DVector> Double3DVector; //!< type definition for 3D matrices of doubles
  typedef std::vector<PhasedArrayModel::ComplexVector> Complex2DVector; //!< type definition for complex matrices
  typedef std::vector<Complex2DVector> Complex3DVector; //!< type definition for complex 3D matrices


  /**
   * Data structure that stores a channel realization
   */
  struct ChannelMatrix : public SimpleRefCount<ChannelMatrix>
  {
    Complex3DVector    m_channel; //!< channel matrix H[u][s][n].
    DoubleVector       m_delay; //!< cluster delay in nanoseconds.
    Double2DVector     m_angle; //!< cluster angle angle[direction][n], where direction = 0(AOA), 1(ZOA), 2(AOD), 3(ZOD) in degree.
    Time               m_generatedTime; //!< generation time
    std::pair<uint32_t, uint32_t> m_nodeIds; //!< the first element is the s-node ID (the transmitter when the channel was generated), the second element is the u-node ID (the receiver when the channel was generated)

    /**
     * Destructor for ChannelMatrix
     */
    virtual ~ChannelMatrix () = default;
    
    /**
     * Returns true if the ChannelMatrix object was generated
     * considering node b as transmitter and node a as receiver.
     * \param aId id of the a node
     * \param bId id of the b node
     * \return true if b is the rx and a is the tx, false otherwise
     */
    bool IsReverse (const uint32_t aId, const uint32_t bId) const
    {
      uint32_t sId, uId;
      std::tie (sId, uId) = m_nodeIds;
      NS_ASSERT_MSG ((sId == aId && uId == bId) || (sId == bId && uId == aId),
                      "This matrix represents the channel between " << sId << " and " << uId);
      return (sId == bId && uId == aId);
    }
  };

  /**
   * Returns a matrix with a realization of the channel between
   * the nodes with mobility objects passed as input parameters.
   *
   * We assume channel reciprocity between each node pair (i.e., H_ab = H_ba^T),
   * therefore GetChannel (a, b) and GetChannel (b, a) will return the same
   * ChannelMatrix object.
   * To understand if the channel matrix corresponds to H_ab or H_ba, we provide
   * the method ChannelMatrix::IsReverse. For instance, if the channel
   * matrix corresponds to H_ab, a call to IsReverse (idA, idB) will return
   * false, conversely, IsReverse (idB, idA) will return true.
   *
   * \param aMob mobility model of the a device
   * \param bMob mobility model of the b device
   * \param aAntenna antenna of the a device
   * \param bAntenna antenna of the b device
   * \return the channel matrix
   */
  virtual Ptr<const ChannelMatrix> GetChannel (Ptr<const MobilityModel> aMob,
                                               Ptr<const MobilityModel> bMob,
                                               Ptr<const PhasedArrayModel> aAntenna,
                                               Ptr<const PhasedArrayModel> bAntenna) = 0;
  
  /**
   * Calculate the channel key using the Cantor function
   * \param x1 first value
   * \param x2 second value
   * \return \f$ (((x1 + x2) * (x1 + x2 + 1))/2) + x2; \f$
   */
  static constexpr uint32_t GetKey (uint32_t x1, uint32_t x2)
  {
   return (((x1 + x2) * (x1 + x2 + 1)) / 2) + x2;
  }

  static const uint8_t AOA_INDEX = 0; //!< index of the AOA value in the m_angle array
  static const uint8_t ZOA_INDEX = 1; //!< index of the ZOA value in the m_angle array
  static const uint8_t AOD_INDEX = 2; //!< index of the AOD value in the m_angle array
  static const uint8_t ZOD_INDEX = 3; //!< index of the ZOD value in the m_angle array

};

}; // namespace ns3

#endif // MATRIX_BASED_CHANNEL_H
